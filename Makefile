# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src
TEST = test
UTIL = src/util
TEST_UTIL = test/util

bitstream.o: $(UTIL)/bitstream.c $(UTIL)/bitstream.h
	$(CC) $(CFLAGS) -c $(UTIL)/bitstream.c -o bitstream.o

bitstream_test.o: bitstream.o $(TEST_UTIL)/bitstream_test.c $(TEST_UTIL)/bitstream_test.h
	$(CC) $(CFLAGS) -c $(TEST_UTIL)/bitstream_test.c -o bitstream_test.o

testrunner.o: testrunner.c bitstream_test.o
	$(CC) $(CFLAGS) -c testrunner.c -o testrunner.o

testrunner: testrunner.o
	$(CC) $(CFLAGS) -o testrunner testrunner.o -libcheck

clean:
	/bin/rm -f *.o testrunner
