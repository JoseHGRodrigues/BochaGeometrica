#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef void *Element; // Void pointer to a generic Element
typedef void *List;    // Void pointer to a linked list

List listInit(); // Initialize a linked list, returning a point

void listFree(List l); // frees memory allocate from the linked list

bool listEmpty(List l); // Check if linked list is empty

bool listPush(List l, Element elem); // Inserts an Element at the end of the linked list

Element listPop(List l); // Removes an Element from the beginning of the linked list

#endif
