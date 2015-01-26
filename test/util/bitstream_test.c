// Original Author: Trevor Killeen (2015)
//
// Test Suite for the bitstream IO class

#include <stdlib.h>
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include "./bitstream_test.h"
#include "../files/test_files.h"
#include "../../src/util/bitstream.h"

struct bitstream *read_bs;
struct bitstream *write_bs;

// todo: figure out why we can't call bitstream_alloc();
struct bitstream *create_bitstream() {
  return (struct bitstream *)calloc(1, sizeof(struct bitstream));
}

void setup() {
  read_bs = create_bitstream();
  write_bs = create_bitstream();
  ck_assert(read_bs != NULL && write_bs != NULL);
}

void teardown() {
  bitstream_destroy(read_bs);
  bitstream_destroy(write_bs);
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

  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
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

  ck_assert_int_eq(read_byte(read_bs, f, &byte), -1);
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
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, expected[i]);
  }
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
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
    ck_assert_int_eq(read_byte(read_bs, f, &byte), 0);
    ck_assert_int_eq(byte, expected[i]);
  }
  ck_assert_int_eq(read_byte(read_bs, f, &byte), -1);
  fclose(f);
}
END_TEST

// Tests for reading byte and bits from a two-byte file
START_TEST(read_mixed_two_byte_file_test)
{
  FILE *f;
  uint8_t byte, bit, i;

  f = fopen(DOUBLE_BYTE_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", DOUBLE_BYTE_FILE);
  }

  // this file contains the letter 'a' followed by a newline.
  // newline in binary: 00001010
  uint8_t byte_expected = 97;
  uint8_t bits_expected[8] = {0, 0, 0, 0, 1, 0, 1, 0};

  // read a byte first
  ck_assert_int_eq(read_byte(read_bs, f, &byte), 0);
  ck_assert_int_eq(byte, byte_expected);

  // then the remaining bits
  for (i = 0; i < 8; i++) {
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, bits_expected[i]);
  }

  ck_assert_int_eq(read_byte(read_bs, f, &byte), -1);
  fclose(f);
}
END_TEST

// Tests that reading a byte tosses away any bits left in the
// bit_buffer
START_TEST(read_mixed_throws_away_buffer_test)
{
  FILE *f;
  uint8_t byte, bit, i;

  f = fopen(DOUBLE_BYTE_FILE, "r");
  if (f == NULL) {
    ck_abort_msg("failed to open file %s", DOUBLE_BYTE_FILE);
  }

  // this file contains the letter 'a' followed by a newline.
  // 'a' in binary: 01100001; \n in decimal is 10
  uint8_t bits_expected[4] = {0, 1, 1, 0};
  uint8_t byte_expected = 10;

  // read some of the bits in the first byte
  for (i = 0; i < 4; i++) {
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, bits_expected[i]);
  }

  // then read the next byte
  ck_assert_int_eq(read_byte(read_bs, f, &byte), 0);
  ck_assert_int_eq(byte, byte_expected);

  // now there should be no bits left to read
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
  fclose(f);
}
END_TEST

// Tests writing a single bit to a file; The rest of the
// byte written should be zero-filled
START_TEST(write_bit_single_bit_test)
{
  FILE *f;
  uint8_t bit, i;

  f = tmpfile();
  if (f == NULL) {
    ck_abort_msg("failed to create tmp file. error: %d\n", errno);
  }

  // write a single bit
  ck_assert_int_eq(write_bit(write_bs, f, 1), 0);

  // assert that the file is still empty as the bit is buffered
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);

  // now flush the file
  ck_assert_int_eq(flush(write_bs, f), 0);

  // the file should be 1000000 in binary
  uint8_t bits_expected[8] = {1, 0, 0, 0, 0, 0, 0, 0};
  ck_assert_int_eq(fseek(f, 0, SEEK_SET), 0);
  for (i = 0; i < 8; i++) {
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, bits_expected[i]);
  }

  // now there should be no bits left to read
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
  fclose(f);
}
END_TEST

// Tests writing 8 bits to a file
START_TEST(write_bit_eight_bits_test)
{
  FILE *f;
  uint8_t bit, i;

  f = tmpfile();
  if (f == NULL) {
    ck_abort_msg("failed to create tmp file. error: %d\n", errno);
  }

  // write the bits to the file
  uint8_t bits_expected[8] = {1, 0, 1, 1, 0, 0, 1, 0};
  for (i = 0; i < 8; i++) {
    ck_assert_int_eq(write_bit(write_bs, f, bits_expected[i]), 0);
  }

  // now read them back in!
  ck_assert_int_eq(fseek(f, 0, SEEK_SET), 0);
  for (i = 0; i < 8; i++) {
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, bits_expected[i]);
  }

  // now there should be no bits left to read
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
  fclose(f);
}
END_TEST

// Tests writing a byte to a file
START_TEST(write_single_byte_test)
{
  FILE *f;
  uint8_t byte;

  f = tmpfile();
  if (f == NULL) {
    ck_abort_msg("failed to create tmp file. error: %d\n", errno);
  }

  ck_assert_int_eq(write_byte(write_bs, f, 23), 0);
  ck_assert_int_eq(fseek(f, 0, SEEK_SET), 0);
  ck_assert_int_eq(read_byte(read_bs, f, &byte), 0);
  ck_assert_int_eq(byte, 23);
  ck_assert_int_eq(read_byte(read_bs, f, &byte), -1);
  fclose(f);
}
END_TEST

// Tests writing 8 bits and a byte to the file
START_TEST(write_mixed_test)
{
  FILE *f;
  uint8_t bit, byte, i;

  f = tmpfile();
  if (f == NULL) {
    ck_abort_msg("failed to create tmp file. error: %d\n", errno);
  }

  // write the bits to the file
  uint8_t bits_expected[8] = {1, 1, 1, 0, 0, 0, 1, 1};
  for (i = 0; i < 8; i++) {
    ck_assert_int_eq(write_bit(write_bs, f, bits_expected[i]), 0);
  }

  // write the byte
  uint8_t byte_expected = 112;
  ck_assert_int_eq(write_byte(write_bs, f, byte_expected), 0);

  // read the bits back in
  ck_assert_int_eq(fseek(f, 0, SEEK_SET), 0);
  for (i = 0; i < 8; i++) {
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, bits_expected[i]);
  }

  // read the byte back in
  ck_assert_int_eq(read_byte(read_bs, f, &byte), 0);
  ck_assert_int_eq(byte, byte_expected);

  // should be EOF
  ck_assert_int_eq(read_byte(read_bs, f, &byte), -1);
  fclose(f);
}
END_TEST

// Tests writing 16 bits to a file
START_TEST(write_bit_sixteen_bits_test)
{
  FILE *f;
  uint8_t bit, i;

  f = tmpfile();
  if (f == NULL) {
    ck_abort_msg("failed to create tmp file. error: %d\n", errno);
  }

  // write the bits to the file
  uint8_t bits_expected[16] = {1,1,0,1,0,0,1,1,0,0,1,0,0,0,1,0};
  for (i = 0; i < 16; i++) {
    ck_assert_int_eq(write_bit(write_bs, f, bits_expected[i]), 0);
  }

  // now read them back in!
  ck_assert_int_eq(fseek(f, 0, SEEK_SET), 0);
  for (i = 0; i < 16; i++) {
    ck_assert_int_eq(read_bit(read_bs, f, &bit), 0);
    ck_assert_int_eq(bit, bits_expected[i]);
  }

  // now there should be no bits left to read
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
  fclose(f);
}
END_TEST

// Tests that writing a byte throws away the contents of the
// stream buffer
START_TEST(write_mixed_throws_away_buffer_test)
{
  FILE *f;
  uint8_t byte, bit, i;

  f = tmpfile();
  if (f == NULL) {
    ck_abort_msg("failed to create tmp file. error: %d\n", errno);
  }

  // write the bits to the file
  uint8_t bits_expected[4] = {1,1,0,1};
  for (i = 0; i < 4; i++) {
    ck_assert_int_eq(write_bit(write_bs, f, bits_expected[i]), 0);
  }

  // write the byte
  uint8_t byte_expected = 47;
  ck_assert_int_eq(write_byte(write_bs, f, byte_expected), 0);

  // read the byte back in
  ck_assert_int_eq(fseek(f, 0, SEEK_SET), 0);
  ck_assert_int_eq(read_byte(read_bs, f, &byte), 0);
  ck_assert_int_eq(byte, byte_expected);

  // now there should be no bits left to read
  ck_assert_int_eq(read_bit(read_bs, f, &bit), -1);
  fclose(f);
}
END_TEST

Suite *bitstream_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("bitstream");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, alloc_test);
  tcase_add_test(tc_core, read_bit_empty_file_test);
  tcase_add_test(tc_core, read_byte_empty_file_test);
  tcase_add_test(tc_core, read_bit_two_byte_file_test);
  tcase_add_test(tc_core, read_byte_two_byte_file_test);
  tcase_add_test(tc_core, read_mixed_two_byte_file_test);
  tcase_add_test(tc_core, read_mixed_throws_away_buffer_test);

  tcase_add_test(tc_core, write_bit_single_bit_test);
  tcase_add_test(tc_core, write_bit_eight_bits_test);
  tcase_add_test(tc_core, write_single_byte_test);
  tcase_add_test(tc_core, write_mixed_test);
  tcase_add_test(tc_core, write_bit_sixteen_bits_test);
  tcase_add_test(tc_core, write_mixed_throws_away_buffer_test);

	suite_add_tcase(s, tc_core);

	return s;
}
