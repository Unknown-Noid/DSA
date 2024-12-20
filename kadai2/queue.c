#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *create_queue(int len) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) {
        exit(EXIT_FAILURE);
        return NULL;
    }
    q->buffer = (int *)malloc(len * sizeof(int));
    if (q->buffer == NULL) {
        exit(EXIT_FAILURE);
        free(q);
        return NULL;
    }
    q->length = len;
    q->front = -1;
    q->rear = -1;
    printf("Queue created!\n");
    return q;
}

void enqueue(Queue *q, int d) {
    if ((q->rear + 1) % q->length == q->front) {
        fprintf(stderr, "Queue is full! Cannot enqueue %d.\n", d);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->length;
    q->buffer[q->rear] = d;
}

int dequeue(Queue *q) {
    if (q->front == -1) {
        fprintf(stderr, "Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    int data = q->buffer[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->length;
    }
    return data;
}

void display(Queue *q) {
    if (q->front == -1) {
        fprintf(stderr, "Queue is empty! Nothing to display.\n");
        return;
    }
    int i = q->front;
    while (1) {
        printf("%d ", q->buffer[i]);
        if (i == q->rear) break;
        i = (i + 1) % q->length;
    }
    printf("\n");
}

void delete_queue(Queue *q) {
    if (q != NULL) {
        free(q->buffer);
        free(q);
        printf("Queue deleted!\n");
    }
}
