########################################################################
#
#  Use this Makefile to build the ZAS for uinx/linux
#
########################################################################
SRCDIR=../
TARGET = zas

CSRCS = code.c cclass.c expr.c lex.c macro.c main.c kwd.c parse.c sym.c tlab.c fname.c
VSRC  = version.c

HDRS  = cclass.h kwd.h zas.h


OBJS = $(CSRCS:.c=.o)
VOBJ = $(VSRC:.c=.o)

CC = gcc
LD = gcc

CFLAGS=-O3 -I$(SRCDIR) -Wall

RM = rm -f

all: version	$(TARGET)

.SUFFIXES:		# delete the default suffixes
VPATH=$(SRCDIR)


%.o: %.c
	$(CC) -c $(CFLAGS) $<

version:
	(cd $(SRCDIR); ../Scripts/gitver.pl -w)

$(TARGET): $(OBJS) $(VOBJ)
	$(CC) -o$@ $(OBJS) $(VOBJ)

$(OBJS) : $(HDRS)

$(VOBJ) : gitVer.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM)  $(TARGET)


