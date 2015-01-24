# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src
TEST = test
UTIL = src/util

bitstream.o : $(UTIL)/bitstream.c $(UTIL)/bitstream.h
	$(CC) $(CFLAGS) -c $(UTIL)/bitstream.c -o bitstream.o

clean:
	/bin/rm -f *.o 
