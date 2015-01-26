# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src
TEST = test
HUFFMAN = src/huffman
TEST_HUFFMAN = test/huffman
UTIL = src/util
TEST_UTIL = test/util

# files
OBJECTS = testrunner.o bitstream_test.o bitstream.o frequency.o frequency_test.o

frequency.o: $(HUFFMAN)/frequency.c $(HUFFMAN)/frequency.h
	$(CC) $(CFLAGS) -c $(HUFFMAN)/frequency.c

frequency_test.o: $(TEST_HUFFMAN)/frequency_test.c $(TEST_HUFFMAN)/frequency_test.h
	$(CC) $(CFLAGS) -c $(TEST_HUFFMAN)/frequency_test.c

bitstream.o: $(UTIL)/bitstream.c $(UTIL)/bitstream.h
	$(CC) $(CFLAGS) -c $(UTIL)/bitstream.c

bitstream_test.o: $(TEST_UTIL)/bitstream_test.c $(TEST_UTIL)/bitstream_test.h
	$(CC) $(CFLAGS) -c $(TEST_UTIL)/bitstream_test.c

testrunner.o: testrunner.c
	$(CC) $(CFLAGS) -c testrunner.c

testrunner: $(OBJECTS)
	$(CC) $(CFLAGS) -o testrunner $(OBJECTS) -lcheck

clean:
	/bin/rm -f *.o testrunner
