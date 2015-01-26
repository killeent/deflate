// Original Author: Trevor Killeen (2015)
//
// Test runner for DEFLATE

#include <stdlib.h>
#include <check.h>

#include "./test/util/bitstream_test.h"
#include "./test/huffman/frequency_test.h"

int main() {
  Suite *bs, *freq;
  SRunner *runner;
  int failures;

  bs = bitstream_suite();
  freq = frequency_suite();

  runner = srunner_create(bs);
  srunner_add_suite(runner, freq);

  // for debugging
  srunner_set_fork_status(runner, CK_NOFORK);

  srunner_run_all(runner, CK_VERBOSE);
  failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures;
}
