CFLAGS += -std=c99 -mfpmath=sse -Ofast -flto -march=native -funroll-loops -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS += -Wmissing-prototypes -Wno-unused-parameter
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/local/bin
CC     ?= gcc

all: qpwm

config.h:
	cp config.def.h config.h
	
qpwm: qpwm.c config.h Makefile
	$(CC) $(CFLAGS) -o $@ $< -lX11 $(LDFLAGS)
	
install: all
	install -Dm755 qpwm $(DESTDIR)$(BINDIR)/qpwm
	
clean:
	rm -f qpwm *.o
	
.PHONY: all install clean
