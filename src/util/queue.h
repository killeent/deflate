// Original Author: Trevor Killeen (2015)

#ifndef _QUEUE_H_
#define _QUEUE_H_

// A simple Queue ADT implemented with a Linked List

struct queue_node {
  struct queue_node *prev;
  struct queue_node *next;
  void *payload;
};

struct queue {
  struct queue_node *head;
  struct queue_node *tail;
};

/**
 * Allocates a new queue.
 *
 * @return a queue, or NULL if error.
 */
struct queue *allocate_queue();

/**
 * Frees the memory associated with the queue.
 *
 * @param q the queue to free.
 * @param free_fn user-specified function to free the contents
 * of queue payloads.
 */
void free_queue(struct queue *q, void (*free_fn)(void *));

/**
 * Adds the specified payload to the back of the queue.
 * 
 * @param q the queue to mutate.
 * @param payload pointer to the payload to add to the queue.
 *
 * @return 0 on success, otherwise error.
 */
int enqueue(struct queue *q, void *payload);

/**
 * Removes and returns the item at the front of the queue.
 *
 * @param q to queue to mutate.
 *
 * @return the item at the from of the queue, or NULL if the
 * queue is empty.
 */
void *dequeue(struct queue *q);

#endif
