SHELL=bash
.PHONY: clean distclean install rebuild
DIRS = cgen cpp cref dehuff dump enhuff hidump hidump2 libr \
       libr4 link mkpat objtohex optim p1 zas zas4 zc
all:
	@for f in $(DIRS); do $(MAKE) -C $$f || exit 1; done;

build:
	@for f in $(DIRS); do $(MAKE) -C $$f build || exit 1; done;

clean: 
	@for f in $(LIBS) $(DIRS); do $(MAKE) -C $$f clean || exit 1; done;

distclean: 
	@for f in $(LIBS) $(DIRS); do $(MAKE) -C $$f distclean || exit 1; done;

install:
	@for f in $(LIBS) $(DIRS); do $(MAKE) -C $$f install || exit 1; done;

rebuild: 
	@for f in $(DIRS); do $(MAKE) -C $$f rebuild || exit 1; done;

publish: 
	@for f in $(DIRS); do $(MAKE) -C $$f publish || exit 1; done;
