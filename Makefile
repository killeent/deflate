# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src
TEST = test
HUFFMAN = src/huffman
UTIL = src/util
TEST_UTIL = test/util

frequency.o: $(HUFFMAN)/frequency.c $(HUFFMAN)/frequency.h
	$(CC) $(CFLAGS) -c $(HUFFMAN)/frequency.c

bitstream.o: $(UTIL)/bitstream.c $(UTIL)/bitstream.h
	$(CC) $(CFLAGS) -c $(UTIL)/bitstream.c

bitstream_test.o: $(TEST_UTIL)/bitstream_test.c $(TEST_UTIL)/bitstream_test.h
	$(CC) $(CFLAGS) -c $(TEST_UTIL)/bitstream_test.c

testrunner.o: testrunner.c
	$(CC) $(CFLAGS) -c testrunner.c

testrunner: testrunner.o bitstream_test.o bitstream.o
	$(CC) $(CFLAGS) -o testrunner testrunner.o bitstream_test.o bitstream.o -lcheck

clean:
	/bin/rm -f *.o testrunner
