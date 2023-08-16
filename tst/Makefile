APPNAME=run_tests
CC=gcc
CCFLAGS=-O2 -Wall
FLAGS_INCLUDE=-I/opt/homebrew/include
FLAGS_LIB=-L/opt/homebrew/lib -L../src -lbotje_base64 -lcmocka
OBJECTS_TESTS=test_botje_base64__decode.o test_botje_base64__encode.o tests.o

all: src tests

clean:
	rm -f $(APPNAME) $(OBJECTS_TESTS)

src:
	$(MAKE) -C ../src

test_botje_base64__decode.o: test_botje_base64__decode.c test_botje_base64__decode.h
	$(CC) $(CCFLAGS) $(FLAGS_INCLUDE) -c -o test_botje_base64__decode.o test_botje_base64__decode.c

test_botje_base64__encode.o: test_botje_base64__encode.c test_botje_base64__encode.h
	$(CC) $(CCFLAGS) $(FLAGS_INCLUDE) -c -o test_botje_base64__encode.o test_botje_base64__encode.c

tests.o: tests.c
	$(CC) $(CCFLAGS) $(FLAGS_INCLUDE) -c -o tests.o tests.c

tests: $(OBJECTS_SHARED) $(OBJECTS_TESTS)
	$(CC) $(CCFLAGS) $(FLAGS_LIB) -o $(APPNAME) $(OBJECTS_TESTS)

run:
	make clean && make && DYLD_LIBRARY_PATH=../src ./run_tests
