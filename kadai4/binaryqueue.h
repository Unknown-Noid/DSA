#ifndef INCLUDE_GUARD_QUEUE_H
#define INCLUDE_GUARD_QUEUE_H
#include "binarytree.h"

typedef struct queue {
  Node **buffer;
  int length;
  int front;
  int rear;
} Queue;

Queue *create_queue(int len);
void enqueue(Queue *q, Node *node);
Node *dequeue(Queue *q);
void display_queue(Queue *q);
void delete_queue(Queue *q);

#endif  // INCLUDE_GUARD_QUEUE_H