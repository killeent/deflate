// Original Author: Trevor Killeen (2015)
//
// Test Suite for the queue implementation

#include "./queue_test.h"
#include "../../src/util/queue.h"

Suite *queue_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("queue");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	suite_add_tcase(s, tc_core);

	return s;
}

