#include <stdio.h>
#include <stdlib.h>
#include "binarysearchtree.h"

Node *create_node(int d, Node *left, Node *right){
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "メモリの割り当てに失敗しました\n");
        exit(EXIT_FAILURE);
    }
    node->value = d;
    node->left = left;
    node->right = right;
    return node;
}

int min_bst(Node *root){
    if(root == NULL)return -1;
    Node *p = root;
    while(p->left != NULL)p = p->left;
    return p->value;
}

bool search_bst(Node *root, int d){
    Node *p = root;
    while(p != NULL){
        if(p->value == d){
            return true;
        } else if (p->value > d){
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return false;
}

void insert_bst(Node **root, int d){
    if(*root == NULL){
        *root = create_node(d, NULL, NULL);
        return;
    }
    Node *p = *root;
    while(1){
        if(p->value == d)return;
        if(p->value > d){
            if(p->left == NULL){
                p->left = create_node(d,NULL,NULL);
                return;
            } else {
                p = p->left;
            }
        } else {
            if(p->right == NULL) {
                p->right = create_node(d,NULL,NULL);
                return;
            } else {
                p = p->right;
            }
        }
    }
}

void delete_bst(Node **root, int d) {
    if (*root == NULL) return;

    Node *p = *root;
    Node *q = NULL;

    while (p != NULL && p->value != d) {
        q = p;
        if (d < p->value) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    if (p == NULL) return;

//case1
    if (p->left == NULL && p->right == NULL) {
        if (q == NULL) {
            *root = NULL;
        } else if (q->left == p) {
            q->left = NULL;
        } else {
            q->right = NULL;
        }
        free(p);

//case2
    } else if (p->left == NULL || p->right == NULL) {
        Node *child = (p->left != NULL) ? p->left : p->right;

        if (q == NULL) {
            *root = child;
        } else if (q->left == p) {
            q->left = child;
        } else {
            q->right = child;
        }
        free(p);

//case3
    } else {
        Node *s = p->right;
        Node *sp = p;

        while (s->left != NULL) {
            sp = s;
            s = s->left;
        }

        p->value = s->value;

        if (sp->left == s) {
            sp->left = s->right;
        } else {
            sp->right = s->right;
        }
        free(s);
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
    printf("%d ", n->value);
    inorder(n->right);
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

    printf("%d(", n->value);
    display(n->left);
    printf(",");
    display(n->right);
    printf(")");

    if (is_first_call == 0 && n == root) {
        printf("\n");
        is_first_call = 1;
    }
}

void delete_tree(Node *n){
    if (n == NULL) return;
    delete_tree(n->left);
    delete_tree(n->right);
    free(n);
}