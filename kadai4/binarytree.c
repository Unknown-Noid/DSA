#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binaryqueue.h"
#include "binarytree.h"

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

void delete_queue(Queue *q) {
    free(q->buffer);
    free(q);
}


Node *create_node(char *label, Node *left, Node *right){
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "メモリの割り当てに失敗しました\n");
        exit(EXIT_FAILURE);
    }
     node->label = (char *)malloc(strlen(label) + 1);
    if (node->label == NULL) {
        fprintf(stderr, "文字列用のメモリ割り当てに失敗しました\n");
        free(node);
        exit(EXIT_FAILURE);
    }
    strcpy(node->label, label);
    node->left = left;
    node->right = right;
    return node;
}

void preorder(Node *n){
    static int is_first_call = 1;
    static Node *root = NULL;

    if (is_first_call) {
        printf("PRE: ");
        is_first_call = 0;
        root = n;
    }
    if (n == NULL) return;
    printf("%s ", n->label);
    preorder(n->left);
    preorder(n->right);
    if(is_first_call == 0 && n == root) {
        printf("\n");
    }
}

void inorder(Node *n){
    static int is_first_call = 1;
    static Node *root = NULL;

    if(is_first_call){
        printf("IN: ");
        is_first_call = 0;
        root = n;
    }
    if (n == NULL) return;
    inorder(n->left);
    printf("%s ", n->label);
    inorder(n->right);
    if (is_first_call == 0 && n == root) {
        printf("\n");
    }
}

void postorder(Node *n){
    static int is_first_call = 1;
    static Node *root = NULL;

    if (is_first_call) {
        printf("POST: ");
        root = n;
        is_first_call = 0;
    }
    if (n == NULL) return;
    postorder(n->left);
    postorder(n->right);
    printf("%s ", n->label);
    if (is_first_call == 0 && n == root) {
        printf("\n");
    }
}

void display(Node *n){
    static int is_first_call = 1;
    static Node *root = NULL;

    if (is_first_call) {
        printf("TREE: ");
        root = n;
        is_first_call = 0;
    }

    if (n == NULL) {
        printf("null");
        return;
    }

    printf("%s(", n->label);
    display(n->left);
    printf(",");
    display(n->right);
    printf(")");

    if (is_first_call == 0 && n == root) {
        printf("\n");
        is_first_call = 1;
    }
}

void breadth_first_search(Node *n){
    if (n == NULL) return;

    Queue *q = create_queue(100); 
    enqueue(q, n);

    printf("BFS: ");
    while (q->front != q->rear) { 
        Node *current = dequeue(q);
        printf("%s ", current->label);

        if (current->left != NULL) enqueue(q, current->left);
        if (current->right != NULL) enqueue(q, current->right);
    }
    printf("\n");
    delete_queue(q); 
}

int height(Node *n){
    if (n == NULL) return 0;
    int left_height = height(n->left);
    int right_height = height(n->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

void delete_tree(Node *n){
    if (n == NULL) return;
    delete_tree(n->left);
    delete_tree(n->right);
    free(n->label);
    free(n);
}