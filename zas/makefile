########################################################################
#
#  Use this Makefile to build the ZAS for HiTech C v3.09 under Linux
#  using John Elliott's zxcc emulator.
#
########################################################################
TARGET = zasx.com
CSRCS = code.c cclass.c expr.c lex.c macro.c main.c kwd.c parse.c sym.c tlab.c\
		emulate.c

HDRS  = cclass.h kwd.h zas.h

NOVARG = start2.obj

OBJS = $(CSRCS:.c=.obj) $(NOVARG)


#CFLAGS=-O -dOLDLIB
#LIBS=LIBCORIG.LIB LIBFORIG.LIB
#CRT=CRTORIG.OBJ 
CFLAGS=-O
LIBS=LIBC.LIB LIBF.LIB
CRT=CRTCPM.OBJ 

ifeq ($(OS),Windows_NT)
RM = del /q
else
RM = rm -f
endif

all:	$(TARGET)

.SUFFIXES:		# delete the default suffixes
.SUFFIXES: .c .obj

%.obj: %.c
	zxc -c -O $(CFLAGS) $<
%.obj: %.as
	zas $<

$(TARGET): $(OBJS) 
	linq -Z -Dzasx.sym -N -C -Mzasx.map -Ptext=0,data,bss -C100H -O$@ $(CRT) $(OBJS) $(LIBS)
#	$(file >$@.in,-Z -Dzas.xym -N -C -Mzas.map -Ptext=0,data,bss -C100H -OP:$@ $(CRT) \)
#	$(foreach O,$(OBJS),$(file >>$@.in,P:$O \))
#	$(file >>$@.in,$(LIBS))
#	zxcc linq <$@.in
#	$(RM) $@.in

$(OBJS) : $(HDRS)

clean:
	$(RM) $(OBJS) *.map *.sym *.sym.sorted

compress:
	enhuff -a ZAS.HUF makefile $(CSRCS) $(HDRS)

