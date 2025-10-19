#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
  void *data;
  struct node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} list;

list *castList(List l) { return (list *)l; }

List listInit() {
  list *l = malloc(sizeof(list));
  if (!l)
    return NULL;
  l->head = NULL;
  l->tail = NULL;
  return (List)l;
}

void listFree(List l, void (*freeData)(void *data)) {
  if (!l)
    return;
  list *lst = castList(l);
  Node *current = lst->head;
  while (current) {
    Node *nodeToFree = current;
    current = current->next;
    if (freeData)
      freeData(nodeToFree->data);
    free(nodeToFree);
  }
  free(lst);
}

int listInsertLast(List l, void *data) {
  if (!l)
    return 0;
  list *lst = castList(l);
  Node *newNode = malloc(sizeof(Node));
  if (!newNode)
    return 0;
  newNode->data = data;
  newNode->next = NULL;
  if (lst->tail) {
    lst->tail->next = newNode;
  }

  lst->tail = newNode;
  if (!lst->head) {
    lst->head = newNode;
  }
  return 1;
}

void *listRemoveFirst(List l) {
  if (!l || listIsEmpty(l))
    return NULL;
  list *lst = castList(l);
  Node *nodeToRemove = lst->head;
  void *data = nodeToRemove->data;
  lst->head = nodeToRemove->next;
  if (!lst->head)
    lst->tail = NULL;
  free(nodeToRemove);
  return data;
}

void *listGetFirst(List l) {
  if (!l || listIsEmpty(l))
    return NULL;
  list *lst = castList(l);
  return lst->head->data;
}

bool listIsEmpty(List l) {
  if (!l)
    return true;
  return castList(l)->head == NULL;
}
