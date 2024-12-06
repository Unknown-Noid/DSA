#include <stdio.h>
#include <stdlib.h>
#include "binarysearchtree.h"

int main(void) {
    // Build a binary search tree
    Node *root = NULL;
    insert_bst(&root, 10);
    insert_bst(&root, 15);
    insert_bst(&root, 18);
    insert_bst(&root, 6);
    insert_bst(&root, 12);
    insert_bst(&root,  20);
    insert_bst(&root,  9);

    inorder(root);
    display(root);

    printf("search_bst 10: %d\n", search_bst(root, 10));
    printf("search_bst 12: %d\n", search_bst(root, 12));
    printf("search_bst 15: %d\n", search_bst(root, 15));
    printf("search_bst 7: %d\n", search_bst(root, 7));
    printf("min_bst: %d\n", min_bst(root));

    delete_bst(&root, 15);

    inorder(root);
    display(root);

    delete_bst(&root, 10);

    inorder(root);
    display(root);

    delete_tree(root);

    root = NULL;
    printf("search_bst 10: %d\n", search_bst(root, 10));

    return EXIT_SUCCESS;
}