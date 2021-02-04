########################################################################
#
#  Use this Makefile to build the CGEN for HiTech C v3.09 under Linux
#  using John Elliott's zxcc emulator.
#
########################################################################

VERSION = 3.0

CSRCS =	2.c \
	3.c \
	4.c \
	setup.c \
	ctype_.c

ASRCS = nularg.asm \
	zcrtcpm.asm \
	1.asm \
	5.asm \
	3_1.asm \
	13D.asm \
	1B2.asm \
	306.asm \
	406.asm \
	6D1.asm \
	76F.asm \
	808.asm \
	B19new.asm \
	1659.asm \
	1680.asm \
	17E0.asm \
	19C1.asm \
	1C6D.asm \
	1C8E.asm \
	1F4B.asm \
	283E.asm \
	2B2A.asm \
	2B79.asm \
	2C5E.asm \
	2CE0.asm \
	2D09.asm \
	3564.asm \
	37ED.asm \
	385B.asm \
	3A79.asm \
	3B65.asm \
	3BC6.asm \
	3CDF.asm \
	3EAA.asm \
	415E.asm \
	4192.asm \
	43EF.asm \
	46F7.asm \
	475C.asm \
	47B2.asm \
	4B89.asm \
	4BE5.asm \
	4C6D.asm \
	4C8B.asm \
	4FCE.asm \
	508A.asm \
	5DF6.asm \
	5F52.asm \
	600E.asm \
	60A8.asm \
	605E.asm \
	61AA.asm \
	63B8.asm \
	6589.asm \
	main.asm \
	libc1.asm \
	libc2.asm \
	libc3.asm \
	libc4.asm \
	libc5.asm

COBJS = $(CSRCS:.c=.obj)
AOBJS = $(ASRCS:.asm=.obj)

OBJS = $(COBJS) $(AOBJS)

all:	$(COBJS) $(AOBJS) cgen.com 

.SUFFIXES:		# delete the default suffixes
.SUFFIXES: .c .obj .asm

$(COBJS): %.obj: %.c
	zxc -c -o  $<

$(AOBJS): %.obj: %.asm
	zxas -n $<
#	zxas -j -n $<

cgen.com: $(OBJS)
	zxcc link -"<" +lkcgen
	sort cgen1.sym | uniq > cgen1.sym.sorted

clean:
	rm -f $(OBJS) cgen1.com *.\$$\$$\$$ cgen1.map cgen1.sym cgen1.sym.sorted

compress:
	enhuff -a CGEN.HUF 2.c 3.c 4.c setup.c ctype_.c nularg.asm zcrtcpm.asm \
	1.asm 5.asm 3_1.asm 13D.asm 1B2.asm 306.asm 406.asm 6D1.asm 76F.asm 808.asm \
	B19new.asm 1659.asm 1680.asm 17E0.asm 19C1.asm 1C6D.asm 1C8E.asm 1F4B.asm \
	283E.asm 2B2A.asm 2B79.asm 2C5E.asm 2CE0.asm 2D09.asm 3564.asm 37ED.asm \
	385B.asm 3A79.asm 3B65.asm 3BC6.asm 3CDF.asm 3EAA.asm 415E.asm 4192.asm \
	43EF.asm 46F7.asm 475C.asm 47B2.asm 4B89.asm 4BE5.asm 4C6D.asm 4C8B.asm \
	4FCE.asm 508A.asm 5DF6.asm 5F52.asm 600E.asm 605E.asm 60A8.asm 61AA.asm \
	63B8.asm 6589.asm main.asm libc1.asm libc2.asm libc3.asm libc4.asm libc5.asm \
	makefile lkcgen cgen.h cgen.sym cgen.com 0.txt STDIO.H Readme_en.txt \
	make_c linkcgen 5.c

compress1:
	enhuff -a SOURCE.HUF 13D.C 1B2.C 306.C 406.C 6D1.C 76F.C 808.C 1659.C \
	1680.C 17E0.C 19C1.C 1C6D.C 1C8E.C 1F4B.C 283E.C 2B2A.C 2B79.C 2C5E.C \
	2CE0.C 2D09.C 3564.C 37ED.C 385B.C 3A79.C 3B65.C 3BC6.C 3CDF.C 3EAA.C \
	415E.C 4192.C 43EF.C 46F7.C 475C.C 47B2.C 4B89.C 4BE5.C 4C6D.C 4C8B.C \
	4FCE.C 508A.C 54B6.C 5CF5.C 5DF6.C 5F52.C 600E.C 60A8.C 605E.C 61AA.C \
	63B8.C 6589.C 6AA2.C 6B1D.C 6B9B.C 6D1C.C nularg.c VFPRINTF.C 
