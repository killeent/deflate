// Original Author: Trevor Killeen (2015)
//
// Test Suite for the Frequency calculator

#include <check.h>

#include "./frequency_test.h"
#include "../../src/huffman/frequency.h"

Suite *frequency_suite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("frequency");
  tc_core = tcase_create("core");

  suite_add_tcase(s, tc_core);
  return s;
}
