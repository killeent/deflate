// Original Author: Trevor Killeen (2015)

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "./bitstream.h"

#define MAX_BITS 8

struct bitstream *bitsream_alloc() {
  struct bitstream *bs;
  bs = (struct bitstream *)malloc(sizeof(struct bitstream));
  if (bs == NULL) {
    return NULL;
  }
  bs->bit_buffer = 0;
  bs->bit_count = 0;
  return bs;
}

void bitstream_destroy(struct bitstream *bs) {
  assert(bs != NULL);
  free(bs);
}

void bitstream_clear(struct bitstream *bs) {
  bs->bit_count = 0;
  bs->bit_buffer = 0;
}

int read_bit(struct bitstream *bs, FILE *f, uint8_t *bit) {
  assert(bs != NULL);
  assert(f != NULL);
  assert(bit != NULL);

  size_t read;

  if (bs->bit_count == 0) {
    // need to read in a new byte  
    read = fread((void *)&(bs->bit_buffer), sizeof(bs->bit_buffer), 1, f);
    if (read == 0) {
      // check for EOF 
      if (feof(f)) {
        return -1;
      } else {
        // an error occurred
        return ferror(f);
      }
    }
    bs->bit_count = MAX_BITS;
  }

  *bit = (bs->bit_buffer & (1 << (bs->bit_count - 1))) >> (bs->bit_count - 1);
  bs->bit_count--;
  return 0;
}

int read_byte(struct bitstream *bs, FILE *f, uint8_t *byte) {
  assert(bs != NULL);
  assert(f != NULL);
  assert(byte != NULL);

  size_t read;

  read = fread((void *)byte, sizeof(*byte), 1, f);
  if (read == 0) {
    // check for EOF 
    if (feof(f)) {
      return -1;
    } else {
      // an error occurred
      return ferror(f);
    }
  }

  // clear bit_buffer
  bs->bit_count = 0;

  return 0;
}

int write_bit(struct bitstream *bs, FILE *f, uint8_t bit) {
  assert(bs != NULL);
  assert(f != NULL);
  assert(bit == 0u || bit == 1u);

  // place the bit in its appropriate slot 
  bs->bit_buffer |= (bit << (MAX_BITS - 1 - bs->bit_count));
  bs->bit_count++;

  // check if we need to write
  if (bs->bit_count == MAX_BITS) {
    return flush(bs, f);
  }

  return 0;
}

int write_byte(struct bitstream *bs, FILE *f, uint8_t byte) {
  assert(bs != NULL);
  assert(f != NULL);

  size_t written;

  written = fwrite((void *)&byte, sizeof(byte), 1, f);
  if (written != 1) {
    return ferror(f);
  } else {
    bitstream_clear(bs);
    return 0;
  }
}

int flush(struct bitstream *bs, FILE *f) {
  assert(bs != NULL);
  assert(f != NULL);

  return write_byte(bs, f, bs->bit_buffer);
}
