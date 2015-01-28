# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src
TEST = test
TEST_FILES = test/files
HUFFMAN = src/huffman
TEST_HUFFMAN = test/huffman
UTIL = src/util
TEST_UTIL = test/util

# files
OBJECTS = testrunner.o bitstream_test.o bitstream.o frequency.o frequency_test.o \
hufftree.o queue.o

frequency.o: $(HUFFMAN)/frequency.c $(HUFFMAN)/frequency.h
	$(CC) $(CFLAGS) -c $(HUFFMAN)/frequency.c

frequency_test.o: $(TEST_HUFFMAN)/frequency_test.c $(TEST_HUFFMAN)/frequency_test.h $(TEST_FILES)/test_files.h
	$(CC) $(CFLAGS) -c $(TEST_HUFFMAN)/frequency_test.c

hufftree.o: $(HUFFMAN)/hufftree.c $(HUFFMAN)/hufftree.h
	$(CC) $(CFLAGS) -c $(HUFFMAN)/hufftree.c

hufftree_test.o: $(TEST_HUFFMAN)/hufftree_test.c $(TEST_HUFFMAN).hufftree_test.h
	$(CC) $(CFLAGS) -c $(TEST_HUFFMAN)/hufftree_test.c

bitstream.o: $(UTIL)/bitstream.c $(UTIL)/bitstream.h
	$(CC) $(CFLAGS) -c $(UTIL)/bitstream.c

bitstream_test.o: $(TEST_UTIL)/bitstream_test.c $(TEST_UTIL)/bitstream_test.h $(TEST_FILES)/test_files.h
	$(CC) $(CFLAGS) -c $(TEST_UTIL)/bitstream_test.c

queue.o: $(UTIL)/queue.c $(UTIL)/queue.h
	$(CC) $(CFLAGS) -c $(UTIL)/queue.c

queue_test.o: $(TEST_UTIL)/queue_test.c $(TEST_UTIL)/queue_test.h
	$(CC) $(CFLAGS) -c $(TEST_UTIL)/queue_test.c

testrunner.o: testrunner.c
	$(CC) $(CFLAGS) -c testrunner.c

testrunner: $(OBJECTS)
	$(CC) $(CFLAGS) -o testrunner $(OBJECTS) -lcheck

clean:
	/bin/rm -f *.o testrunner
