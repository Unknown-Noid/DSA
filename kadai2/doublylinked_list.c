#include <stdio.h>
#include <stdlib.h>
#include "doublylinked_list.h"

// セルを作成する関数
Cell *CreateCell(int d, bool is_head) {
    Cell *new_cell = (Cell *)malloc(sizeof(Cell));
    if (new_cell == NULL) {
        exit(EXIT_FAILURE);
        return NULL;
    }
    new_cell->data = d;
    new_cell->is_head = is_head;
    new_cell->prev = new_cell;
    new_cell->next = new_cell;
    return new_cell;
}

// 指定セルの次にセルを挿入する関数
void InsertNext(Cell *this_cell, Cell *p) {
    if (this_cell == NULL || p == NULL) return;
    p->next = this_cell->next;
    p->prev = this_cell;
    this_cell->next->prev = p;
    this_cell->next = p;
}

// 指定セルの前にセルを挿入する関数
void InsertPrev(Cell *this_cell, Cell *p) {
    if (this_cell == NULL || p == NULL) return;
    p->prev = this_cell->prev;
    p->next = this_cell;
    this_cell->prev->next = p;
    this_cell->prev = p;
}

// セルを削除する関数
void DeleteCell(Cell *this_cell) {
    if (this_cell == NULL || this_cell->is_head) return;
    this_cell->prev->next = this_cell->next;
    this_cell->next->prev = this_cell->prev;
    free(this_cell);
}

// データを検索する関数
Cell *SearchCell(Cell *this_cell, int d) {
    if (this_cell == NULL) return NULL;
    Cell *current = this_cell;
    do {
        if (current->data == d) {
            return current;
        }
        current = current->next;
    } while (current != this_cell);
    return NULL;
}

// リストの内容を表示する関数
void Display(Cell *this_cell) {
    if (this_cell == NULL) return;
    Cell *current = this_cell;
    do {
        if (!(current->is_head)) {
            printf("%d ", current->data);
        }
        current = current->next;
    } while (current != this_cell);
    printf("\n");
}
