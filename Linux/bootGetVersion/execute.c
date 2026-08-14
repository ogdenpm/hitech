
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
#include <io.h>
#include <process.h>
typedef intptr_t pid_t;
#define PIPE_BUF    4096
#define pipe(p) _pipe(p, PIPE_BUF, _O_TEXT | O_NOINHERIT)
#else
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#endif

#include "support.h"


#define PIPELEN 256
enum { PREAD = 0, PWRITE = 1 };



int execute(char const *const *cmd, string_t *str, bool isInteractive) {
    int pipes[2];
    char buf[PIPE_BUF];
    int oldStdout;
    int oldStderr;

    if (str) {
        str->pos = 0;       // reset any previous string
        if (pipe(pipes) == -1) {
            fprintf(stderr, "pipe failed\n");
            exit(1);
        }
        if (!isInteractive) {
            oldStdout = dup(fileno(stdout));
            dup2(pipes[PWRITE], fileno(stdout));
        }
        oldStderr = dup(fileno(stderr));
        dup2(pipes[PWRITE], fileno(stderr));
        close(pipes[PWRITE]);
    }


#ifdef _MSC_VER
    intptr_t pid = spawnvp(_P_NOWAIT, "git.exe", cmd);
#else
    pid_t pid;
    if ((pid = fork()) == 0) {
        execvp("git", (char * const *)cmd);
        fatal("exec failed");
    }
#endif
    int status;
    if (str) {
        if (!isInteractive)
            dup2(oldStdout, fileno(stdout));
        dup2(oldStderr, fileno(stderr));
    }
    if (pid > 0) {
        if (str) {
            str->pos = 0;
            int actual;
            while ((actual = (int)read(pipes[PREAD], buf, sizeof(buf))))
                appendBuffer(str, buf, actual);
            appendBuffer(str, "", 1);
        }
#ifdef _MSC_VER
        _cwait(&status, pid, _WAIT_CHILD);
#else
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
#endif
    } else
        status = -1;
    if (str)
        close(pipes[PREAD]);
    return status;
}
