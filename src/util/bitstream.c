#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "./bitstream.h"

struct bitstream *bitsream_alloc() {
  return (struct bitstream *)malloc(sizeof(struct bitstream));
}

void bitstream_destroy(struct bitstream *bs) {
  free(bs);
}

int read_bit(struct bitstream *bs, FILE *f, uint8_t *bit) {
  return 0;
}

int read_byte(struct bitstream *bs, FILE *f, uint32_t *byte) {
  return 0;
}

int write_bit(struct bitstream *bs, FILE *f, uint8_t bit) {
  return 0;
}

int write_byte(struct bitstream *bs, FILE *f, uint32_t byte) {
  return 0;
}

int flush(struct bitstream *bs, FILE *f) {
  return 0;
}
