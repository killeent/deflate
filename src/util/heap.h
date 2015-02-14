// Original Author: Trevor Killeen (2015)

#ifndef _HEAP_H_
#define _HEAP_H_

/**
 * A binary heap. A binary heap is a complete binary tree where
 * for any node n in the tree, b is either greater than or
 * equal to its children, or less than or equal to its children,
 * according to some comparsion function for the heap.
 */ 

struct heap {
	void **elements;						// array-based representation of the tree
	int (*comparsion_fn)(void *, void *);	// function that defines the heap ordering
	unsigned int capacity;					// size of the elements array
	unsigned int count;						// number of elements in the queue
};

/*
 * Allocate a new heap.
 *
 * @param comparsion_fn function that will define the heap ordering.
 * @param initial_capacity specifies the initial capacity of the heap.
 *
 * @return a newly allocated heap, or NULL if out of memory.
 */
struct heap *allocate_heap(
	int (comparsion_fn)(void *, void *), unsigned int initial_capacity);

/**
 * Frees the memory associated with the heap.
 *
 * @param hp the heap to free.
 * @param free_fn user-specified function to free the contents
 * of heap elements.
 */
void free_heap(struct heap *hp, void (free_fn)(void *));

/**
 * Add the specified element to the heap.
 *
 * @param hp heap to mutate.
 * @param elt element to add to the heap.
 *
 * @return 0 on success, otherwise error.
 */
int heap_add(struct heap *hp, void *elt);

/**
 * Removes and returns the element at the top of the heap.
 *
 * @param hp heap to mutate.
 *
 * @return the element at the top of the heap if one exists, otherwise
 * NULL if the heap is empty. It is the client's responsibility to free
 * the memory associated with this element.
 */
void *heap_remove(struct heap *hp);

/**
 * Returns but does not remove the element at the top of the heap.
 *
 * @param hp heap to mutate.
 *
 * @return the element at the top of the heap if one exists, otherwise
 * NULL if the heap is empty.
 */
void *heap_peek(struct heap *hp);

/**
 * Get the number of elements in the heap.
 *
 * @param hp the heap to query.
 *
 * @return the number of elements in the heap.
 */
unsigned int heap_count(struct heap *hp);

#endif