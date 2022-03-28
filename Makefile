CFLAGS += -std=c99 -mfpmath=sse -Ofast -flto -march=native -funroll-loops -Wall -Wextra -pedantic -Wmissing-prototypes -Wno-unused-parameter -lX11 -Wold-style-declaration
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/local/bin
CC     ?= gcc

all: qpwm

config.h:
	cp config.def.h config.h
	
qpwm: qpwm.c config.h Makefile
	$(CC) $(CFLAGS) -o $@ $<
	
install: all
	install -Dm755 qpwm $(DESTDIR)$(BINDIR)/qpwm
	
clean:
	rm -f qpwm *.o
	
.PHONY: all install clean
