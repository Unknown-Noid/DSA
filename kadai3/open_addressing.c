#include <stdio.h>
#include <stdlib.h>
#include "open_addressing.h"

DictOpenAddr *create_dict(int len){
    DictOpenAddr *dict = (DictOpenAddr *)malloc(sizeof(DictOpenAddr));
    if (dict == NULL) {
        fprintf(stderr, "Memory allocation failed for dictionary.\n");
        exit(EXIT_FAILURE);
    }
    dict->H = (DictData *)malloc(len * sizeof(DictData));
    if (dict->H == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table.\n");
        free(dict);
        exit(EXIT_FAILURE);
    }
    dict->B = len;
    for (int i = 0; i < len; i++) {
        dict->H[i].name = 0;
        dict->H[i].state = EMPTY;
    }
    return dict;
}

int h(DictOpenAddr *dict, int d, int count){
    int B = dict->B;
    int h_0 = d % B;
    return (h_0 + count) % B;
}

void insert_hash(DictOpenAddr *dict, int d){
    if (search_hash(dict, d) != -1) {
        return;
    }
    int count = 0; 
    int b = h(dict, d, count);
    int init_b = b;
    do {
        if (dict->H[b].state == EMPTY || dict->H[b].state == DELETED) {
            dict->H[b].name = d;
            dict->H[b].state = OCCUPIED;
            return;
        }
        count++; 
        b = h(dict, d, count);    //rehush
        if (count >= dict->B) {
            fprintf(stderr, "ERROR: Hash table is full. Cannot insert %d.\n", d);
            exit(EXIT_FAILURE);
        }
    } while (b != init_b);
    return;
}

int search_hash(DictOpenAddr *dict, int d){
    int count = 0; 
    int b = h(dict, d, count);
    int init_b = b;
    do {
        if(dict->H[b].state == OCCUPIED && dict->H[b].name == d) {
            return b;
        }
        else if (dict->H[b].state == EMPTY) {
            return -1;
        }
        count++;
        b = h(dict, d, count);    //rehush
    } while (b != init_b);
    return -1;
}

void delete_hash(DictOpenAddr *dict, int d){
    int b = search_hash(dict, d);
    if (b == -1) {
        return;
    }
    dict->H[b].state = DELETED;
}

void display(DictOpenAddr *dict){
    for (int i = 0; i < dict->B; i++) {
        switch(dict->H[i].state){
            case OCCUPIED:
                printf("%d ", dict->H[i].name);
                break;
            case EMPTY:
                printf("e ");
                break;
            case DELETED:
                printf("d ");
                break;
        }
    }
    printf("\n");
}

void delete_dict(DictOpenAddr *dict){
    if (dict != NULL) {
        free(dict->H);
        free(dict);
    }
}