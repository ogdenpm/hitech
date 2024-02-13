########################################################################
#
#  Use this Makefile to build the P1.COM for HiTech C v3.09 under Linux
#  or Windows
########################################################################
# replace the following with your tool versions as required
# Note I use my own version of zc which uses the -Axxx option to specify
# various link parameters and libraries modify the CFLAGS as appropriate
# -DTINY is used for building with the minimal I/O package, omit if you
#  are using standard libraries
#  Note if the environment variable HITECH is not defined
#  then include the appropriate export HITECH=path for your system
########################################################################

CC	= zc
CFLAGS = -O -ACPM2 -DTINY
LIBS = libtiny.lib
# PASSWORD = -pmark

ifeq ($(OS),Windows_NT)
export HITECH=d:\local\lib\cpm
RM = del /q
else
RM = rm -f
endif

TARGET = p1.com

CSRCS = cclass.c emit.c expr.c lex.c main.c op.c program.c stmt.c sym.c type.c

HDRS  = tok.h cclass.h p1.h

OBJS = $(CSRCS:.c=.obj)


all:	$(TARGET)

.SUFFIXES:		# delete the default suffixes
.SUFFIXES: .c .obj

%.obj: %.c
	$(CC) $(CFLAGS) -v -c $<

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -o$(TARGET) -M -F $(OBJS) $(LIBS)

$(OBJS) : $(HDRS)

clean:
	$(RM) *.obj *.map *.sym *.i *.p1

distclean: clean
	$(RM) $(TARGET) p1.7z

compress: $(TARGET)
	7z a $(PASSWORD) -mhe p1.7z $(CSRCS) $(HDRS) $(TARGET) $(LIBS) memchk.c
