// Original Author: Trevor Killeen (2015)
//
// Test runner for DEFLATE

#include <stdlib.h>
#include <check.h>

#include "./test/util/bitstream_test.h"
#include "./test/util/queue_test.h"
#include "./test/util/directory_util_test.h"
#include "./test/util/heap_test.h"
#include "./test/huffman/frequency_test.h"

int main() {
  Suite *bs, *queue, *dir_util, *heap, *freq;
  SRunner *runner;
  int failures;

  bs = bitstream_suite();
  freq = frequency_suite();
  dir_util = directory_util_suite();
  heap = heap_suite();
  queue = queue_suite();

  runner = srunner_create(bs);
  srunner_add_suite(runner, queue);
//  srunner_add_suite(runner, dir_util);
  srunner_add_suite(runner, heap);
  srunner_add_suite(runner, freq);

  // for debugging
  srunner_set_fork_status(runner, CK_NOFORK);

  srunner_run_all(runner, CK_VERBOSE);
  failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures;
}
