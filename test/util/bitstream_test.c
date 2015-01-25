// Original Author: Trevor Killeen (2015)
//
// Test Suite for the bitstream IO class

#include <check.h>
#include <stdint.h>
#include <stdio.h>

#include "./bitstream_test.h"
#include "../../src/util/bitstream.h"

#define EMPTY_FILE "./test/util/files/empty.txt"
#define DOUBLE_BYTE_FILE "./test/util/files/single.txt"

struct bitstream *bs;

void setup() {
	// todo: figure out why we can't call bitstream_alloc();
	bs = (struct bitstream *)malloc(sizeof(struct bitstream));
	ck_assert(bs != NULL);
}

void teardown() {
	bitstream_destroy(bs);
}

// Basic test for allocating/freeing a bitstream
START_TEST(alloc_test)
{
}
END_TEST

// Tests for reading a bit from an empty file
START_TEST(read_bit_empty_file_test)
{
  FILE *f;
  uint8_t bit;

  f = fopen(EMPTY_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", EMPTY_FILE);
  }

  ck_assert_int_eq(read_bit(bs, f, &bit), -1);
  fclose(f);
}
END_TEST

// Tests for reading a byte from an empty file
START_TEST(read_byte_empty_file_test)
{
  FILE *f;
  uint8_t byte;

  f = fopen(EMPTY_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", EMPTY_FILE);
  }

  ck_assert_int_eq(read_byte(bs, f, &byte), -1);
  fclose(f);
}
END_TEST

// Tests reading the bits from a two byte file (char + newline)
START_TEST(read_bit_two_byte_file_test)
{
  FILE *f;
  uint8_t bit, i;

  f = fopen(DOUBLE_BYTE_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", DOUBLE_BYTE_FILE);
  }

  // this file contains the letter 'a' followed by a newline.
  // on a little-endian machine (e.g. x86_64) this is represented
  // by the following bit sequence:
  //
  // 01100001 00001010

  uint8_t expected[16] = {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0};
  for (i = 0; i < 16; i++) {
    ck_assert_int_eq(read_bit(bs, f, &bit), 0);
    ck_assert_int_eq(bit, expected[i]);
  }
  ck_assert_int_eq(read_bit(bs, f, &bit), -1);
  fclose(f);
}
END_TEST

// Tests for reading bytes from a two-byte file
START_TEST(read_byte_two_byte_file_test)
{
  FILE *f;
  uint8_t byte, i;

  f = fopen(DOUBLE_BYTE_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", DOUBLE_BYTE_FILE);
  }

  // this file contains the letter 'a' followed by a newline.
  uint8_t expected[2] = {97, 10};

  for (i = 0; i < 2; i++) {
    ck_assert_int_eq(read_byte(bs, f, &byte), 0);
    ck_assert_int_eq(byte, expected[i]);
  }
  ck_assert_int_eq(read_byte(bs, f, &byte), -1);
  fclose(f);
}
END_TEST

Suite *bitstream_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("bitstream");

	tc_core = tcase_create("Core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, alloc_test);
  tcase_add_test(tc_core, read_bit_empty_file_test);
  tcase_add_test(tc_core, read_byte_empty_file_test);
  tcase_add_test(tc_core, read_bit_two_byte_file_test);
  tcase_add_test(tc_core, read_byte_two_byte_file_test);

	suite_add_tcase(s, tc_core);

	return s;
}
