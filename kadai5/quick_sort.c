#include "quick_sort.h"

int partition(int a[], int pivot, int left, int right) {
    int value = a[right];
    a[right] = a[pivot];
    a[pivot] = value;
    int l = left;
    int r = right - 1;
    while(1){
        while(a[l] < a[right]) l = l + 1;
        while(l <= r && a[r] >= a[right]) r = r - 1;
        if(l < r){
            value = a[l];
            a[l] = a[r];
            a[r] = value;
        }else{
            break;
        }
    }
    value = a[l];
    a[l] = a[right];
    a[right] = value;
    return l;
}

void quick_sort_recursive(int a[], int left, int right){
    if(left < right){
        int pivot = left;
        int p = partition(a, pivot, left, right);

        quick_sort_recursive(a, left, p-1);
        quick_sort_recursive(a, p+1, right);
    }
}

void quick_sort(int a[], int n) {
    quick_sort_recursive(a, 0, n-1);
}