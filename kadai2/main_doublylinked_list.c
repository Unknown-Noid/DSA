#include <stdio.h>
#include <stdlib.h>
#include "doublylinked_list.h"

int main(void) {
    // Cell *head = CreateCell(0, true);
    // printf("Initial list created with head node.\n");

    // printf("\n== Inserting cells ==\n");
    // Cell *first = CreateCell(1, false); 
    // InsertNext(head, first);           

    // Cell *middle = CreateCell(2, false); 
    // InsertNext(first, middle);           

    // Cell *last = CreateCell(3, false); 
    // InsertPrev(head, last);           

    // Display(head); 

    
    // printf("\n== Checking unconnected cell ==\n");
    // Cell *unconnected = CreateCell(4, false); 
    // if (unconnected->next == unconnected && unconnected->prev == unconnected) {
    //     printf("Warning: Cell with data %d is not connected to the list.\n", unconnected->data);
    // }

    // printf("\n== Deleting cells ==\n");
    // DeleteCell(first);  
    // Display(head);       

    // DeleteCell(last);    
    // Display(head);      

    // DeleteCell(middle);  
    // Display(head);       

    // printf("\n== Reinserting and searching for cells ==\n");
    // Cell *new_first = CreateCell(1, false); 
    // Cell *new_middle = CreateCell(2, false); 
    // Cell *new_last = CreateCell(3, false);   

    // InsertNext(head, new_first);    
    // InsertNext(new_first, new_middle); 
    // InsertPrev(head, new_last);    
    // Display(head);                  

    // printf("\nSearching for cells:\n");
    // Cell *found;
    // found = SearchCell(head, 1); 
    // if (found != NULL) printf("Found cell with data 1 at address %p\n", (void *)found);
    // else printf("Cell with data 1 not found.\n");

    // found = SearchCell(head, 2);
    // if (found != NULL) printf("Found cell with data 2 at address %p\n", (void *)found);
    // else printf("Cell with data 2 not found.\n");

    // found = SearchCell(head, 3); 
    // if (found != NULL) printf("Found cell with data 3 at address %p\n", (void *)found);
    // else printf("Cell with data 3 not found.\n");

    // DeleteCell(new_first);
    // DeleteCell(new_middle);
    // DeleteCell(new_last);

    // free(head);
    // printf("\nList and all cells deleted.\n");

    
    Cell *head = CreateCell(0, true);
    printf("Initial list created with head node.\n");
   
    printf("\n== ReadFromArray() Test ==\n");
    int data[] = {1, 2, 3, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);
    ReadFromArray(head, data, size);
    printf("List after reading from array: ");
    Display(head);

    printf("\n== WriteToArray() Test ==\n");
    int output[10]; 
    int output_size;
    WriteToArray(head, output, &output_size);
    printf("Array after writing from list: ");
    for (int i = 0; i < output_size; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    printf("\n== WriteToFile() Test ==\n");
    const char *filename = "output.txt";
    WriteToFile(head, filename);
    printf("List data written to file '%s'\n", filename);

    printf("\n== ReadFromFile() Test ==\n");
  
    while (head->next != head) {
        DeleteCell(head->next);
    }
    printf("List cleared.\n");

    ReadFromFile(head, filename);
    printf("List after reading from file: ");
    Display(head);
    
    while (head->next != head) {
        DeleteCell(head->next);
    }
    free(head);
    printf("\nList and all cells deleted.\n");

    return EXIT_SUCCESS;
}