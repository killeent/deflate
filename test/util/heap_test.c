// Original Author: Trevor Killeen (2015)
//
// Test Suite for the queue implementation

#include <stdlib.h>
#include <assert.h>

#include "./heap_test.h"
#include "../../src/util/heap.h"

// global heap for testing
static struct heap *hp;

// comparison function for a min heap of integers
static int int_cmp_fn(void *int_a, void *int_b) {
	return *((int *)int_a) - *((int *)int_b);
}

static void free_int(void *int_ptr) {
  free(int_ptr);
}

static void setup() {
	hp = allocate_heap(int_cmp_fn, 11);
	assert(hp != NULL);
}

static void teardown() {
	free_heap(hp, free_int);
}

Suite *heap_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("heap");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	suite_add_tcase(s, tc_core);

	return s;
}