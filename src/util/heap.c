// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "./heap.h"

// helper function declarations
static void bubble_up(struct heap *hp, unsigned int index);
static void bubble_down(struct heap *hp, unsigned int index);
static int expand_heap(struct heap *hp);

struct heap *allocate_heap(
		int (*comparsion_fn)(void *, void *), unsigned int initial_capacity) {
	assert(comparsion_fn != NULL);

	struct heap *hp;

	hp = (struct heap *)malloc(sizeof(struct heap));
	if (hp == NULL) {
		return NULL;
	}
	hp->elements = (void **)calloc(initial_capacity, sizeof(void *));
	if (hp->elements == NULL) {
		free(hp);
		return NULL;
	}
	hp->comparsion_fn = comparsion_fn;
	hp->capacity = initial_capacity;
	hp->count = 0;

	return hp;
}

void free_heap(struct heap *hp, void (free_fn)(void *)) {
	assert(hp != NULL);
	assert(free_fn != NULL);

	unsigned int i;

	for (i = 0; i < hp->count; i++) {
		free_fn(hp->elements[i]);
	}

	free(hp->elements);
	free(hp);
}

int heap_add(struct heap *hp, void *elt) {
	assert(hp != NULL);
	assert(elt != NULL);

	int res;

	// ensure enough capacity for new element
	if (hp->count == hp->capacity) {
		res = expand_heap(hp);
		if (res) {
			return res;
		}
	}

	hp->elements[hp->count] = elt;
	bubble_up(hp, hp->count);
	hp->count++;
	return 0;
}

void *heap_remove(struct heap *hp) {
	assert(hp != NULL);

	void *res;

	if (hp->count == 0) {
		return NULL;
	}
	res = hp->elements[0];
	hp->count--;
	hp->elements[0] = hp->elements[hp->count];
	bubble_down(hp, 0);
	return res;
}

void *heap_peek(struct heap *hp) {
	assert(hp != NULL);
	return hp->count == 0 ? NULL : hp->elements[0];
}

unsigned int heap_count(struct heap *hp) {
	assert(hp != NULL);
	return hp->count;
}

// doubles the size of the heap
static int expand_heap(struct heap *hp) {
	assert(hp != NULL);

	void **copy;
	unsigned int i;

	// create a copy of the elements array with twice the capacity
	copy = (void **)calloc(hp->capacity * 2, sizeof(void *));
	if (copy == NULL) {
		return ENOMEM;
	}
	for (i = 0; i < hp->count; i++) {
		copy[i] = hp->elements[i];
	}
	hp->capacity *= 2;
	free(hp->elements);
	hp->elements = copy;
	return 0;
}

// bubble up the value at index, swapping it with its parent
// as long as it has higher priority (lower priority value)
static void bubble_up(struct heap *hp, unsigned int index) {
	assert(hp != NULL);

	int parent;
	void *temp;

	parent = (index - 1) / 2;
	while (parent >= 0 && 
			hp->comparsion_fn(hp->elements[parent], hp->elements[index]) < 0) {
		temp = hp->elements[parent];
		hp->elements[parent] = hp->elements[index];
		hp->elements[index] = temp;
		index = parent;
		parent = (index - 1) / 2;
	}
}

// bubble down the value at index, swapping it repeatedly with
// its max priority (lowest priority value) child as long as
// it has higher priority than the parent
static void bubble_down(struct heap *hp, unsigned int index) {
	assert(hp != NULL);

	unsigned int left_child, right_child, max_child;
	void *temp;

	left_child = index * 2 + 1;
	right_child = index * 2 + 2;

	while (left_child < hp->count) {
		if (right_child < hp->count) {
			max_child = hp->comparsion_fn(
				hp->elements[left_child], hp->elements[right_child]) < 0 ?
				left_child :
				right_child;
		} else {
			max_child = left_child;
		}

		if (hp->comparsion_fn(hp->elements[max_child], hp->elements[index]) < 0) {
			temp = hp->elements[index];
			hp->elements[index] = hp->elements[max_child];
			hp->elements[max_child] = temp;
			index = max_child;
			left_child = index * 2 + 1;
			left_child = index * 2 + 2;
		} else {
			break;
		}
	}
}







