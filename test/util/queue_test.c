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

// tests simple enqueue and dequeue from the queue
START_TEST(simple_enqueue_dequeue_test) {
  int *data;

  data = (int *)malloc(sizeof(int));
  ck_assert(data != NULL);
  
  ck_assert_int_eq(enqueue(q, (void *)data), 0);
  ck_assert_ptr_eq((int *)dequeue(q), data);

  free(data);
}
END_TEST

// test dequeue returns NULL from an empty queue
START_TEST(dequeue_empty_queue_test)
{
  ck_assert_ptr_eq(dequeue(q), NULL);
}
END_TEST

// tests queue maintains ordering
START_TEST(queue_maintains_ordering_test)
{
  int *a, *b, *c;

  a = (int *)malloc(sizeof(int));
  ck_assert(a != NULL);
  b = (int *)malloc(sizeof(int));
  ck_assert(b != NULL);
  c = (int *)malloc(sizeof(int));
  ck_assert(c != NULL);
  
  // enqueue 3 items and check that they are dequeued
  // in the correct order
  ck_assert_int_eq(enqueue(q, (void *)a), 0);
  ck_assert_int_eq(enqueue(q, (void *)b), 0);
  ck_assert_int_eq(enqueue(q, (void *)c), 0);
  ck_assert_ptr_eq((int *)dequeue(q), a);
  ck_assert_ptr_eq((int *)dequeue(q), b);
  ck_assert_ptr_eq((int *)dequeue(q), c);

  free(a);
  free(b);
  free(c);

}
END_TEST

// todo: add tests for interleaved ordering; freeing empty, single
// and multi-element queues

Suite *queue_suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("queue");

	tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, allocation_test);
  tcase_add_test(tc_core, simple_enqueue_dequeue_test);
  tcase_add_test(tc_core, dequeue_empty_queue_test);
  tcase_add_test(tc_core, queue_maintains_ordering_test);

	suite_add_tcase(s, tc_core);

	return s;
}

