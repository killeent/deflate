// Original Author: Trevor Killeen (2015)
//
// Test runner for DEFLATE

#include <stdlib.h>
#include <check.h>

#include "./test/util/bitstream_test.h"

int main() {
  Suite *s;
  SRunner *runner;
  int failures;

  s = bitstream_suite();
  runner = srunner_create(s);

  // for debugging
  srunner_set_fork_status(runner, CK_NOFORK);

  srunner_run_all(runner, CK_VERBOSE);
  failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures;
}
