// Original Author: Trevor Killeen (2015)
//
// Test Suite for the bitstream IO class

#include <check.h>
#include <stdint.h>
#include <stdio.h>

#include "./bitstream_test.h"
#include "../../src/util/bitstream.h"

#define EMPTY_FILE "./test/util/files/empty.txt"

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
}
END_TEST

// Tests for reading a byte from an empty file
START_TEST(read_byte_empty_file_test)
{
  FILE *f;
  uint8_t bit;

  f = fopen(EMPTY_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", EMPTY_FILE);
  }

  ck_assert_int_eq(read_bit(bs, f, &bit), -1);
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

	suite_add_tcase(s, tc_core);

	return s;
}
