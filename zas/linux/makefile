########################################################################
#
#  Use this Makefile to build the ZAS for uinx/linux
#
########################################################################
SRCDIR=../
TARGET = zas

CSRCS = code.c cclass.c expr.c lex.c macro.c main.c kwd.c parse.c sym.c tlab.c fname.c

HDRS  = cclass.h kwd.h zas.h


OBJS = $(CSRCS:.c=.o)

CC = gcc
LD = gcc

CFLAGS=-O3 -I$(SRCDIR) -Wall

RM = rm -f

all:	$(TARGET)

.SUFFIXES:		# delete the default suffixes
VPATH=$(SRCDIR)


%.o: %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS) 
	$(CC) -o$@ $(OBJS)

$(OBJS) : $(HDRS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM)  $(TARGET)


