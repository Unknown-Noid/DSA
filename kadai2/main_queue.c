#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
  Queue *test_q = create_queue(5);

  //1
  printf("== Test 1: Enqueue one element and dequeue it ==\n");
  enqueue(test_q, 10);
  display(test_q);
  printf("Dequeued: %d\n", dequeue(test_q));
  display(test_q);

  //2
  printf("\n== Test 2: Enqueue multiple elements and dequeue them in order ==\n");
  enqueue(test_q, 20);
  enqueue(test_q, 30);
  enqueue(test_q, 40);
  display(test_q);
  printf("Dequeued: %d\n", dequeue(test_q));
  printf("Dequeued: %d\n", dequeue(test_q));
  display(test_q);

  //3
  printf("\n== Test 3: Wrap-around case ==\n");
  enqueue(test_q, 50);
  enqueue(test_q, 60);
  enqueue(test_q, 70);
  enqueue(test_q, 80);  
  display(test_q);

  printf("Dequeued: %d\n", dequeue(test_q));  
  display(test_q);

  enqueue(test_q, 90);  
  display(test_q);

  //4
  printf("\n== Test 4: Queue empty and full conditions ==\n");

  enqueue(test_q, 100); 

  while (test_q->front != -1) {
      printf("Dequeued: %d\n", dequeue(test_q));
  }
  display(test_q);

  printf("Attempt to dequeue from empty queue:\n");
  dequeue(test_q);  

  delete_queue(test_q);

  return EXIT_SUCCESS;
}