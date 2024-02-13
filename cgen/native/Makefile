OBJ = data.obj lex1u.obj lex2.obj code.obj sym1.obj sym2s.obj\
	  sym3.obj cgen1.obj cgen2s.obj cgen3.obj tree1.obj tree2.obj tree3.obj\
	  local1s.obj local2.obj main.obj malloc.obj getchar.obj

AS = $(OBJ:.obj=.as)
# the build target
# NOTE do not use cgen.com as the zxc tools will try to use it from
# this directory which can cause very odd behaviour
TARGET = xcgen.com

# turn off curses, it creates lots of screen flicker
# and PDCurses doesn't allow redirect
export CPMTERM=TERMIOS
# the makefile assumes that zxc tools are setup on an appropriate PATH
# and that the cross compiled optim file is also on the PATH
# modify the lines below if this does not apply for your installation
# additionally the unpack.pl file assumes that perl is installed on your
# system. For unix and variants it uses #! to find perl. Update
# unpack.pl if it is not in the expected location
# Note windows builds will need a version of zxc ported to windows.
# I have done this myself and added in changes to auto close files
# before deleting them. The raw port of zxc fails as windows does
# note allow open files to be deleted and the hitech compiler does
# not explicitly close files open for reading only
#
ifeq ($(OS),Windows_NT)
  OPTIM = optim
  RM = del
  MV = move /y
else
  OPTIM = optim
  RM = rm -f
  MV = mv
endif

# the last letter of the file name, pre the .c is used to determine the build steps
# if it is s then this requires the ported optimiser
# if it is u then this is unoptimised
# else its a normal optimised file
#
%s.as:%s.c
	zxc -s $<
	$(OPTIM) <$*s.as >tmp.as
	$(MV) tmp.as $*s.as

%u.as:%u.c
	zxc -s $<

%.as:%.c
	zxc -s -O $<

%.obj:%.as
	zxas $<


all: unpack
	$(MAKE) $(TARGET)

clean:
	$(RM) $(OBJ) $(AS)

distclean: clean
	$(RM) $(TARGET) $(OBJ:.obj=.c) cgen.h

$(TARGET): $(OBJ)
	$(file >$@.in,-Z -Ptext=0,data,bss -C100H -OP:$@ -Mxcgen.map -Dxcgen.sym crtcpm.obj \)
	$(foreach O,$(OBJ),$(file >>$@.in,P:$O \))
	$(file >>$@.in,LIBC.LIB)
	zxcc linq <$@.in
	$(RM) $@.in

unpack:
	./unpack.pl

$(AS) : cgen.h



