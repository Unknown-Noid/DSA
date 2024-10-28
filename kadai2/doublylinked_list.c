#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "doublylinked_list.h"

Cell *CreateCell(int d, bool is_head) {
    Cell *new_cell = (Cell *)malloc(sizeof(Cell));
    if (new_cell == NULL) {
        exit(EXIT_FAILURE);
    }
    new_cell->data = d;
    new_cell->is_head = is_head;
    new_cell->prev = new_cell;
    new_cell->next = new_cell;

    if (!is_head) {
        printf("Warning: Cell with data %d is not connected to the list.\n", d);
    }
    return new_cell;
}

void InsertNext(Cell *this_cell, Cell *p) {
    if (this_cell == NULL || p == NULL) return;
    p->next = this_cell->next;
    p->prev = this_cell;
    this_cell->next->prev = p;
    this_cell->next = p;
}

void InsertPrev(Cell *this_cell, Cell *p) {
    if (this_cell == NULL || p == NULL) return;
    p->prev = this_cell->prev;
    p->next = this_cell;
    this_cell->prev->next = p;
    this_cell->prev = p;
}

void DeleteCell(Cell *this_cell) {
    if (this_cell == NULL || this_cell->is_head) return;
    this_cell->prev->next = this_cell->next;
    this_cell->next->prev = this_cell->prev;
    free(this_cell);
}

Cell *SearchCell(Cell *this_cell, int d) {
    if (this_cell == NULL) return NULL;

    Cell *current = this_cell->next; 
    while (current != this_cell) {
        if (current->data == d) {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}

void Display(Cell *this_cell) {
    if (this_cell == NULL) return;
    Cell *current = this_cell->next;
    while (!current->is_head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void ReadFromArray(Cell *head, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        InsertPrev(head, CreateCell(arr[i], false));
    }
}

void WriteToArray(Cell *head, int arr[], int *size) {
    int i = 0;
    Cell *current = head->next;
    while (!current->is_head) {
        arr[i++] = current->data;
        current = current->next;
    }
    *size = i;
}

void ReadFromFile(Cell *head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        InsertPrev(head, CreateCell(value, false));
    }
    fclose(file);
}

void WriteToFile(Cell *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    Cell *current = head->next;
    while (!current->is_head) {
        fprintf(file, "%d ", current->data);
        current = current->next;
    }
    fprintf(file, "\n");
    fclose(file);
}
