########################################################################
#
#  Use this Makefile to build the .COM for HiTech C v3.09 under Linux
#  using John Elliott's zxcc emulator.
#  See notes in the text for local changes required. Assumes C only
#  source. modify to meet your requirements
#
########################################################################
# change for file to be built the SRC and include files needed
# note to help mix optimised / unoptimised and problematic files that
# need to be optimised with the ported optimiser the last character of
# the file name before the .c extension is used to control the build
# if the character is a u - the file is compiled without optimisation
# if the character is an s - the file is optimised using the ported optimiser
# otherwise the file is built using the native optim program
TARGET  = link.com
SRC		= a.c b.c c.c ds.c e.c
INCLUDE	= link.h

DISTFILES = $(SRC) $(INCLUDE) Makefile
DISTYPE	= 7z
# DISTYPE = huff
#
# the build tools and basic linker flags
CC      = zxc
AS		= zxas
LD		= zxcc linq
OPTIM   = optim
LFLAGS  = -Z -Ptext=0,data,bss -C100H

# macros to support build under windows / linux / unix
ifeq ($(OS),Windows_NT)
  RM = del
  MV = move /y
  SORTUNIQ = sort /unique
  TYPE = type
  7Z = c:\Program Files\7-Zip\7z
else
  RM = rm -f
  MV = mv
  SORTUNIQ = sort | uniq
# removes from ^Z to end of file in unix variants
  TYPE = sed  -e "/\cZ/,$$ d"
  7Z = 7z
endif

# turn off curses, it creates lots of screen flicker
# and PDCurses doesn't allow redirect
export CPMTERM=TERMIOS

OBJ = $(SRC:.c=.obj)


.PHONY: all clean compress

all:	$(TARGET) 

$(TARGET): $(OBJ)
	$(file >$@.in,$(LFLAGS) -D$(@:.com=.sym) -M$(@:.com=.map) -OP:$@ crtcpm.obj \)
	$(foreach O,$(OBJ),$(file >>$@.in,P:$O \))
	$(file >>$@.in,LIBC.LIB)
	$(LD) <$@.in
	$(RM) $@.in
	$(TYPE) $(@:.com=.sym) | $(SORTUNIQ) > $(@:.com=.sym.sorted)

# build rules
# for more than one include file the rules here may be sub-optimal

%s.obj:%s.c $(INCLUDE)
	$(CC) -s $<
	$(OPTIM) <$*s.as >tmp.as
	$(MV) tmp.as $*s.as
	$(AS) $*s.as
	$(RM) $*s.as

%u.obj:%u.c $(INCLUDE)
	$(CC) -c $<

%.obj:%.c $(INCLUDE)
	$(CC) -c -O $<

%.obj:%.as
	zxas $<

clean:
	$(RM) $(TARGET) $(OBJ) *.map *.sym *.sym.sorted *.huf *.7z

# set your preferred compression
compress: $(TARGET:.com=.$(DISTYPE))

$(TARGET:.com=.huf): $(DISTFILES)
	enhuff -a $@ $(DISTFILES)

$(TARGET:.com=.7z): $(DISTFILES)
	$(7Z) a $@ $(DISTFILES)
