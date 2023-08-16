CC=gcc

all: botje_base64.o libbotje_base64.so

clean:
	rm -f botje_base64.o libbotje_base64.so

install:
	cp botje_base64.h /opt/homebrew/include/botje_base64.h
	cp libbotje_base64.so /opt/homebrew/lib/libbotje_base64.so

uninstall:
	rm -f /opt/homebrew/include/botje_base64.h
	rm -f /opt/homebrew/lib/libbotje_base64.so

botje_base64.o: botje_base64.c botje_base64.h
	$(CC) -O2 -Wall -c -o botje_base64.o botje_base64.c

libbotje_base64.so: botje_base64.o
	$(CC) -O2 -Wall -dynamiclib -o libbotje_base64.so botje_base64.o
