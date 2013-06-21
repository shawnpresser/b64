
prefix=/usr/local
progname=b64

b64:
	gcc b64.c b64_main.c -o b64

all: b64

clean:
	rm -f *.o
	rm -f ./b64

install: b64
	install -m 0755 ./b64 $(prefix)/bin

.PHONY: all install

