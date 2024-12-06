#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "double_hashing.h"

DictDoubleHashing *create_dict(int len){
    DictDoubleHashing *dict = (DictDoubleHashing *)malloc(sizeof(DictDoubleHashing));
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

int g(int d, int B) {
    return 1 + (d % (B - 1));
}

int h(DictDoubleHashing *dict, int d, int count) {
    int B = dict->B;
    int h_0 = d % B;
    int hash_value = (h_0 + count * g(d, B)) % B;
    return hash_value;
}

void insert_hash(DictDoubleHashing *dict, int d) {
    if (search_hash(dict, d) != -1) {
        return; 
    }
    int count = 0;
    int b = h(dict, d, count);
    int MAX_REHASH_ATTEMPTS = dict->B;

    while (count < MAX_REHASH_ATTEMPTS) {
        if (dict->H[b].state == EMPTY || dict->H[b].state == DELETED) {
            dict->H[b].name = d;
            dict->H[b].state = OCCUPIED;
            return;
        }
        count++;
        b = h(dict, d, count);
    }
    fprintf(stderr, "ERROR: Hash table is full or rehash limit exceeded. Cannot insert %d.\n", d);
    exit(EXIT_FAILURE);
}

int search_hash(DictDoubleHashing *dict, int d) {
    int count = 0;
    int b = h(dict, d, count);
    int MAX_REHASH_ATTEMPTS = dict->B;

    while (count < MAX_REHASH_ATTEMPTS) {
        if (dict->H[b].state == OCCUPIED && dict->H[b].name == d) {
            return b;
        } else if (dict->H[b].state == EMPTY) {
            return -1;
        }
        count++;
        b = h(dict, d, count);
    }
    return -1;
}

void delete_hash(DictDoubleHashing *dict, int d){
    int b = search_hash(dict, d);
    if (b == -1) {
        return;
    }
    dict->H[b].state = DELETED;
}

void display(DictDoubleHashing *dict){
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

void delete_dict(DictDoubleHashing *dict){
    if (dict != NULL) {
        free(dict->H);
        free(dict);
    }
}

