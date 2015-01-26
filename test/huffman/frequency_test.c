// Original Author: Trevor Killeen (2015)
//
// Test Suite for the Frequency calculator

#include <check.h>

#include "./frequency_test.h"
#include "../files/test_files.h"
#include "../../src/huffman/frequency.h"

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

Suite *frequency_suite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("frequency");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, empty_file_test);

  suite_add_tcase(s, tc_core);
  return s;
}
