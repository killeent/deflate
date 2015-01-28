// Original Author: Trevor Killeen (2015)
//
// Test Suite for the queue implementation

#include <stdlib.h>
#include <assert.h>

#include "./queue_test.h"
#include "../../src/util/queue.h"

// global queue for testing
struct queue *q;

static void free_int(void * pl) {
  free(pl);
}

static void setup() {
  q = allocate_queue();
  assert(q != NULL);
}

void teardown() {
  free_queue(q, free_int);
}

// tests simple allocation and free of an empty queue
START_TEST(allocation_test)
{
}
END_TEST

Suite *queue_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("queue");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, allocation_test);

	suite_add_tcase(s, tc_core);

	return s;
}

