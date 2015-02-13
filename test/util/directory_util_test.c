// Original Author: Trevor Killeen (2015)
//
// Test Suite for the directory util implementation

#include "./directory_util_test.h"
#include "../../src/util/queue.h"
#include "../../src/util/directory_util.h"

static void setup() {	
}

static void teardown() {	
}

Suite *directory_util_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("directory_util");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	suite_add_tcase(s, tc_core);

	return s;
}