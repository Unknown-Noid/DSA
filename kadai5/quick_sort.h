#ifndef INCLUDE_GUARD_quick_SORT_H
#define INCLUDE_GUARD_quick_SORT_H

int partition(int a[], int pivot, int left, int right);
void quick_sort(int a[], int n);
void quick_sort_recursive(int a[], int left, int right); //add

#endif