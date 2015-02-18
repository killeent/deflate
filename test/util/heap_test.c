// Original Author: Trevor Killeen (2015)
//
// Test Suite for the queue implementation.

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

// tests than an empty heap is considered empty
START_TEST(empty_heap_count_test)
{
	ck_assert_int_eq(heap_count(hp), 0);
}
END_TEST

// tests peek on an empty heap returns NULL
START_TEST(empty_heap_peek_test)
{
	ck_assert_ptr_eq(heap_peek(hp), NULL);
}
END_TEST

// tests remove on an empty heap returns NULL
START_TEST(empty_heap_remove_test)
{
	ck_assert_ptr_eq(heap_peek(hp), NULL);
}
END_TEST

// tests API functions on a single element heap
START_TEST(single_element_heap_test)
{
	int *val;

	val = (int *)malloc(sizeof(int));
	ck_assert(val != NULL);
	*val = 1;

	heap_add(hp, (void *)val);
	ck_assert_int_eq(heap_count(hp), 1);
	ck_assert_int_eq(*((int *)heap_peek(hp)), 1);
	ck_assert_int_eq(*((int *)heap_remove(hp)), 1);
	ck_assert_int_eq(heap_count(hp), 0);

	free(val);
}
END_TEST

Suite *heap_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("heap");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, empty_heap_count_test);
	tcase_add_test(tc_core, empty_heap_peek_test);
	tcase_add_test(tc_core, empty_heap_remove_test);
	tcase_add_test(tc_core, single_element_heap_test);

	suite_add_tcase(s, tc_core);

	return s;
}