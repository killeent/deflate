// Original Author: Trevor Killeen (2015)
//
// Test Suite for the Frequency calculator

#include <stdlib.h>
#include <check.h>

#include "./frequency_test.h"
#include "../files/test_files.h"
#include "../../src/huffman/frequency.h"

// Tests for error when trying to get the frequency of characters
// in a missing file
START_TEST(missing_file_test)
{
  unsigned long *freqs;
  unsigned int len;

  char *missing = "./notafile.txt";

  ck_assert_int_ne(calc_frequencies(missing, &freqs, &len), 0);
}
END_TEST

// Tests that an empty file can be read but has frequency
// of zero for all characters
START_TEST(empty_file_test)
{
  unsigned long *freqs;
  unsigned int len, i;

  ck_assert_int_eq(calc_frequencies(EMPTY_FILE, &freqs, &len), 0);
  
  for(i = 0; i < len; i++) {
    ck_assert_int_eq(freqs[i], 0);
  }
}
END_TEST

// Tests getting the character counts for a simple file containing
// a single character and newline character
START_TEST(simple_file_test)
{
  unsigned long *freqs;
  unsigned int len, i;

  // file contains 'a' (ASCII 97) and '\n' (ASCII 10)
  ck_assert_int_eq(calc_frequencies(DOUBLE_BYTE_FILE, &freqs, &len), 0);
  for (i = 0; i < len; i++) {
    if (i == 10 || i == 97) {
      ck_assert_int_eq(freqs[i], 1);
    } else {
      ck_assert_int_eq(freqs[i], 0);
    }
  }
    
  free(freqs);
}
END_TEST

Suite *frequency_suite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("frequency");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, empty_file_test);
  tcase_add_test(tc_core, missing_file_test);
  tcase_add_test(tc_core, simple_file_test);

  suite_add_tcase(s, tc_core);
  return s;
}
