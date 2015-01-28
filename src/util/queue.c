// Original Author: Trevor Killeen (2015)

#include <stdlib.h>
#include "./queue.h"

struct queue *allocate_queue() {
  return NULL;
}

void free_queue(struct queue *q, void (*free_fn)(void *)) {
}

int enqueue(struct queue *q, void *payload) {
  return 0;
}

void *dequeue(struct queue *q) {
  return NULL;
}
