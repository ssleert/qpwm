CFLAGS += -std=c99 -Wall -Wextra -Wpedantic -Wold-style-declaration -Wunused-variable
CFLAGS += -Wmissing-prototypes -Wno-unused-parameter -Wmissing-field-initializers
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/local/bin
CC     ?= gcc

all: qpwm

config.h:
	cp config.def.h config.h

qpwm: qpwm.c qpwm.h config.h Makefile
	$(CC) -O3 $(CFLAGS) -o $@ $< -lX11 -lXext -lXinerama $(LDFLAGS)

install: all
	install -Dm755 qpwm $(DESTDIR)$(BINDIR)/qpwm

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/qpwm

clean:
	rm -f qpwm *.o

.PHONY: all install uninstall clean
