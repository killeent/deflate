// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include <assert.h>
#include "./queue.h"

struct queue *allocate_queue() {
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  if (q == NULL) {
    return NULL;
  }
  q->head = q->tail = NULL;
  q->count = 0;
  return q;
}

void free_queue(struct queue *q, void (*free_fn)(void *)) {
  assert(q != NULL);
  assert(free_fn != NULL);  

  void *iter;

  while ((iter = dequeue(q)) != NULL) {
    free_fn(iter);
  }

  free(q);
}

int enqueue(struct queue *q, void *payload) {
  assert(q != NULL);
  assert(payload != NULL);

  struct queue_node *n =
    (struct queue_node *)malloc(sizeof(struct queue_node));
  if (n == NULL) {
    return 1;
  }
  n->payload = payload;
  
  if (q->head == NULL && q->tail == NULL) {
    // queue is empty
    q->head = q->tail = n;
  } else {
    q->tail->next = n;
    q->tail = n;
  }
  q->count++;
  return 0;
}

void *dequeue(struct queue *q) {
  assert(q != NULL);

  struct queue_node *temp;
  void *res;

  if (q->head == NULL) {
    return NULL;
  } else {
    res = q->head->payload;
    if (q->head == q->tail) {
      // only one element in queue
      free(q->head);
      q->head = q->tail = NULL;
    } else {
      temp = q->head;
      q->head = q->head->next;
      free(temp); 
    }
    q->count--;
    return res;
  }
}

unsigned int queue_count(struct queue *q) {
  assert(q != NULL);

  return q->count;
}
