# Known transcription bugs in `LIBRARY.HUF`

Two `.asm` files inside `LIBRARY.HUF` (Andrey Nikitin's disassembly bundle)
contain transcription errors in their left "Disassembled version" column.
Both are inert in current builds: the prebuilt `LIBC.LIB` from `agn453/HI-TECH-Z80-C/dist/`
provides working `sprintf` and `_pnum` implementations, and the two affected files are
typically excluded when assembling a `libcrt.lib` from the bundle. They will bite anyone
who tries to assemble these files unmodified.

In each case the right-column comment (`; After compiling C source code`) preserves the
correct mnemonic; the bug is in the left column that `zas` actually assembles.

## `sprintf.asm:21`

```
        ld      hl,32767
        ld      (_spf+2),h      ;       ld      (_spf+2),hl     <-- BUG: missing L register
```

`ld (nn),h` is not a valid Z80 instruction (the only single-register absolute store is
`ld (nn),a`). The intent is the 16-bit `ld (nn),hl` shown in the right-column comment.

**Fix:** change `ld (_spf+2),h` to `ld (_spf+2),hl`.

## `pnum.asm:56`

```
        call    __pnum          ;       call    _pnum           <-- BUG: extra leading underscore
```

`__pnum` (two underscores) is undefined; the function is defined at `pnum.asm:26` as
`_pnum` (one underscore) and the call here is intended to be a recursion. The right-column
comment confirms.

**Fix:** change `call __pnum` to `call _pnum`.

## Resolution status

Documentation-only. The `.HUF` archive itself is preserved verbatim as Nikitin contributed
it; correcting these one-character mistakes in-place would require re-Huffman'ing the
50-file bundle and replacing the contributed binary. That decision belongs upstream
(`markogden/hitech`).

Anyone unpacking `LIBRARY.HUF` to rebuild `libcrt.lib` should apply the two fixes above
before invoking `zas` on these files.
