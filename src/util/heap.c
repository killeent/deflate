// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include <assert.h>

#include "./heap.h"

// helper function declarations
static void bubble_up(struct heap *hp, unsigned int index);
static void bubble_down(struct heap *hp, unsigned int index);
static int expand_heap(struct heap *hp);

struct heap *allocate_heap(
		int (*comparsion_fn)(void *, void *), unsigned int initial_capacity) {
	assert(comparsion_fn != NULL);

	return NULL;
}

void free_heap(struct heap *hp, void (free_fn)(void *)) {
	assert(hp != NULL);
	assert(free_fn != NULL);
}

int heap_add(struct heap *hp, void *elt) {
	assert(hp != NULL);
	assert(elt != NULL);

	return 0;
}

void *heap_remove(struct heap *hp) {
	assert(hp != NULL);

	return NULL;
}

void *heap_peek(struct heap *hp) {
	assert(hp != NULL);

	return NULL;
}

unsigned int heap_count(struct heap *hp) {
	assert(hp != NULL);

	return hp->count;
}