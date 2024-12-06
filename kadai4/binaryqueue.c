#include <stdio.h>
#include <stdlib.h>
#include "binaryqueue.h"

Queue *create_queue(int len) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->buffer = (Node **)malloc(len * sizeof(Node *)); 
    q->length = len;
    q->front = q->rear = 0;
    return q;
}

void enqueue(Queue *q, Node *node) {
    if ((q->rear + 1) % q->length == q->front) {
        printf("Queue is full\n");
        return;
    }
    q->buffer[q->rear] = node;
    q->rear = (q->rear + 1) % q->length;
}

Node *dequeue(Queue *q) {
    if (q->front == q->rear) {
        printf("Queue is empty\n");
        return NULL;
    }
    Node *node = q->buffer[q->front];
    q->front = (q->front + 1) % q->length;
    return node;
}

void display_queue(Queue *q) {
    int i = q->front;
    while (i != q->rear) {
        printf("%s ", q->buffer[i]->label); 
        i = (i + 1) % q->length;
    }
    printf("\n");
}

void delete_queue(Queue *q) {
    free(q->buffer);
    free(q);
}
