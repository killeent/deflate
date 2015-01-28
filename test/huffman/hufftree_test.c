// Original Author: Trevor Killeen (2015)
//
// Test Suite for the HuffTree

#include <check.h>

#include "./hufftree_test.h"
#include "../../src/huffman/hufftree.h"

Suite *hufftree_suite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("hufftree");
  tc_core = tcase_create("core");

  suite_add_tcase(s, tc_core);
  return s;
}

