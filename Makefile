VERSION=2020-9

RM=/bin/rm
PREFIX?=/usr/local
LIB_SUFFIX?=lib
MANPREFIX?=$(PREFIX)/share/man
TWOBWM_PATH?=${PREFIX}/bin/2bwm
X11_INCLUDE?=/usr/local/include

#CC=clang
DIST=2bwm-$(VERSION)
SRC=main.c list.h list.c hidden.c config.c config.h definitions.h types.h
DISTFILES=Makefile README.md TODO 2bwm.man $(SRC)
CFLAGS+=-Os -s -I${X11_INCLUDE} \
		-DTWOBWM_PATH=\"${TWOBWM_PATH}\"

LDFLAGS+=-L${PREFIX}/${LIB_SUFFIX} -lxcb -lxcb-randr -lxcb-keysyms \
		 -lxcb-icccm -lxcb-ewmh -lxcb-xrm
TARGETS=hidden 2bwm
OBJS=$(SRC:%.c=%.o)

all: $(TARGETS)

2bwm: main.o list.o config.o
	$(CC) -o $@ $(CFLAGS) main.o list.o config.o $(LDFLAGS)

hidden: hidden.o
	$(CC) -o $@ $(CFLAGS) hidden.o $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

install: $(TARGETS)
	test -d $(DESTDIR)$(PREFIX)/bin || mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -pm 755 2bwm $(DESTDIR)$(PREFIX)/bin
	install -pm 755 hidden $(DESTDIR)$(PREFIX)/bin
	test -d $(DESTDIR)$(MANPREFIX)/man1 || mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	install -pm 644 2bwm.man $(DESTDIR)$(MANPREFIX)/man1/2bwm.1
	install -pm 644 hidden.man $(DESTDIR)$(MANPREFIX)/man1/hidden.1

uninstall: deinstall
deinstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/2bwm
	$(RM) $(DESTDIR)$(MANPREFIX)/man1/2bwm.1
	$(RM) $(DESTDIR)$(PREFIX)/bin/hidden
	$(RM) $(DESTDIR)$(MANPREFIX)/man1/hidden.1

$(DIST).tar.bz2:
	mkdir $(DIST)
	cp $(DISTFILES) $(DIST)/
	tar cf $(DIST).tar --exclude .git $(DIST)
	bzip2 -9 $(DIST).tar
	$(RM) -rf $(DIST)

dist: $(DIST).tar.bz2

clean:
	$(RM) -f $(TARGETS) *.o

distclean: clean
	$(RM) -f $(DIST).tar.bz2
