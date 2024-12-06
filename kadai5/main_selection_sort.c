#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selection_sort.h"
#include "sort_util.h"
#include <time.h>

int* test_random_data(int n){
    int* data = (int*)malloc(n * sizeof(int));
    if(!data){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; i++){
        data[i] = rand() % 100;
    }
    return data;
}

void check(int const* data, int n, char const* name) {
    int* a = (int*)calloc(n, sizeof(int));
    memcpy(a, data, n * sizeof(n));

    display(a, n);
    selection_sort(a, n);
    display(a, n);

    if (!is_sorted(a, n)) {
        fprintf(stderr, "Error: %s\n", name);
        exit(EXIT_FAILURE);
    }

    free(a);
}

int main(void) {
    srand((unsigned int)time(NULL));

    for (int n = 5; n < 10; n++) {
        int* data = test_random_data(n);
        check(data, n, "random data");
        free(data);
    }

    return 0;
}