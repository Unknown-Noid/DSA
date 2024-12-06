#include "insertion_sort.h"

void insertion_sort(int a[], int n) {
    for(int i = 1; i < n; i++){
        int d = a[i];
        int j = i - 1;
        while(j >= 0 && d < a[j]){
            a[j+1] = a[j];
            j = j - 1;
        }
        a[j+1] = d;
    }
}