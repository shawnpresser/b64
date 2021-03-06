
prefix=/usr/local

b64:
	gcc -g -O2 b64.c b64_main.c -o b64

all: b64

clean:
	rm -f *.o
	rm -f ./b64

install: b64
	install -m 0755 ./b64 $(prefix)/bin

uninstall:
	rm -f $(prefix)/bin/b64

.PHONY: all clean install uninstall

