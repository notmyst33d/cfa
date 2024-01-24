CC=cc
AR=ar
CFLAGS=-Wall -O2 -std=c89

all: bins lib

bins:
	mkdir -p bin
	$(CC) $(CFLAGS) cfa.c cfapak.c -o bin/cfapak
	$(CC) $(CFLAGS) cfa.c cfaunpak.c -o bin/cfaunpak

lib:
	$(CC) $(CFLAGS) cfa.c -c -o cfa.o
	$(AR) r libcfa.a cfa.o
	$(CC) $(CFLAGS) -shared libcfa.a -o libcfa.so

clean:
	rm -rf bin *.o *.a
