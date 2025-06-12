.PHONY: all install chkversion

SRCDIR=$(subst /Linux,,$(realpath .))
ROOT:=$(realpath ../..)
INSTALLDIR = $(ROOT)/Linux/Install

CFLAGS = -O3 -Wall -I$(SRCDIR) -I$(ROOT)/hishared
VPATH = $(SRCDIR):$(ROOT)/hishared

all:  $(TARGET) | $(INSTALLDIR)
	cp -p $(TARGET) $(INSTALLDIR)

$(INSTALLDIR):
	mkdir -p $@

publish: distclean mkversion
	$(MAKE)

# check version and force timestamp change so build
# information is updated
mkversion:
	(cd $(SRCDIR); perl $(ROOT)/Scripts/getVersion.pl -W)

# check version and only force build if it has changed
chkversion:
	(cd $(SRCDIR); perl $(ROOT)/Scripts/getVersion.pl -w)

_version.o: _version.h _appinfo.h _version.c appinfo.h

$(TARGET): $(OBJS) _version.o
	gcc -o $@ $^

clean:
	rm -f *.o 

distclean: clean
	rm -f $(TARGET)

rebuild: distclean
	$(MAKE) all
