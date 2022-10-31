CC=gcc

all: botje_base64.o libbotjebase64.so

clean:
	rm -f botje_base64.o libbotjebase64.so

install:
	cp libbotjebase64.so /opt/homebrew/lib/libbotjebase64.so
	cp botje_base64.h /opt/homebrew/include/botje_base64.h

uninstall:
	rm -f /opt/homebrew/lib/libbotjebase64.so
	rm -f /opt/homebrew/include/botje_base64.h

botje_base64.o: botje_base64.c botje_base64.h
	$(CC) -c -o botje_base64.o botje_base64.c

libbotjebase64.so: botje_base64.o
	$(CC) -shared -o libbotjebase64.so botje_base64.o
