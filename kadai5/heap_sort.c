#include "heap_sort.h"
#include <math.h>

void sift_down(int a[], int i, int n) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && a[left] > a[largest]){
        largest = left;
    }
    if(right < n && a[right] > a[largest]){
        largest = right;
    }
    if(a[largest] > a[i]){
        int lvalue = a[i];
        a[i] = a[largest];
        a[largest] = lvalue;
        sift_down(a, largest, n);
    }
}

void build_heap(int a[], int n) {
    for(int x = n/2-1; x >= 0; x--){
        sift_down(a, x, n);
    }
}

void heap_sort(int a[], int n) {
    build_heap(a, n);
    for(int m = n-1; m > 0; m--){
        int tmp = a[0];
        a[0] = a[m];
        a[m] = tmp;
        sift_down(a, 0, m);
    }
} 