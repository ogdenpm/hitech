########################################################################
#
#  Use this Makefile to build the ZAS for HiTech C v3.09
#  using John Elliott's zxcc emulator.
#
########################################################################
SRCDIR=../
TARGET = zas.cqm
MAP=$(TARGET:.cqm=.map)
SYM=$(TARGET:.cqm=.sym)

CSRCS = code.c cclass.c expr.c lex.c macro.c main.c kwd.c parse.c sym.c tlab.c fname.c

HDRS  = cclass.h kwd.h zas.h

NOVARG = start2.obj

OBJS = $(CSRCS:.c=.obj) $(NOVARG)

CC = zxc
AS = zxas
LD = zxlink

#CFLAGS=-O -dOLDLIB
#LIBS=LIBCORIG.LIB LIBFORIG.LIB
#CRT=CRTORIG.OBJ 
CFLAGS=-O -I +$(SRCDIR)
LIBS=libc.lib libf.lib
CRT=crtcpm.obj 

ifeq ($(OS),Windows_NT)
RM = del /q
else
RM = rm -f
endif

all:	$(TARGET)

.SUFFIXES:		# delete the default suffixes
VPATH=$(SRCDIR)


%.obj: %.c
	$(CC) -c $(CFLAGS) $<

%.obj: %.as
	$(AS) -o +$@ $< 

$(TARGET): $(OBJS) 
	$(file >$@.in,-Z -D$(SYM) -N -C -M$(MAP) -Ptext=0,data,bss -C100H -O$@ $(CRT) \)
	$(foreach O,$(OBJS),$(file >>$@.in, $O \))
	$(file >>$@.in,$(LIBS))
	$(LD) <$@.in
	$(RM) $@.in

$(OBJS) : $(HDRS)

clean:
	$(RM) $(OBJS) *.map *.sym 
distclean: clean
	$(RM)  $(TARGET)


compress:
	enhuff -a ZAS.HUF makefile $(CSRCS) $(HDRS)

