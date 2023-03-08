########################################################################
#
#  Use this Makefile to build the ZAS for uinx/linux
#
########################################################################
SRCDIR=../
TARGET = zas

CSRCS = code.c cclass.c expr.c lex.c macro.c main.c kwd.c parse.c sym.c tlab.c fname.c version.c

HDRS  = cclass.h kwd.h zas.h


OBJS = $(CSRCS:.c=.o)

CC = gcc
LD = gcc

CFLAGS=-O3 -I$(SRCDIR) -Wall -DAUTOVER

RM = rm -f

all: version	$(TARGET)

.SUFFIXES:		# delete the default suffixes
VPATH=$(SRCDIR)


%.o: %.c
	$(CC) -c $(CFLAGS) $<

version:
	(cd $(SRCDIR); ../Scripts/version.pl Generated/ Generated/version.h)

$(TARGET): $(OBJS) 
	$(CC) -o$@ $(OBJS)

$(OBJS) : $(HDRS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM)  $(TARGET)


