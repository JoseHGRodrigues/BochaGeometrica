#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
  void *data;
  struct node *next;
} Node;

typedef struct {
  Node *top;
  int size;
} stack;

Stack stackInit() {
  stack *st = malloc(sizeof(stack));
  if (st == NULL)
    return NULL;
  st->top = NULL;
  st->size = 0;
  return (Stack)st;
}

void stackFree(Stack s) {
  if (s == NULL)
    return;
  stack *st = (stack *)s;
  Node *currentNode = st->top;
  while (currentNode != NULL) {
    Node *nodeToFree = currentNode;
    currentNode = currentNode->next;
    free(nodeToFree);
  }
  free(st);
}

bool stackIsEmpty(Stack s) {
  if (s == NULL)
    return true;
  stack *st = (stack *)s;
  return st->size == 0;
}

int stackPush(Stack s, void *data) {
  if (s == NULL)
    return 0;
  stack *st = (stack *)s;
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL)
    return 0;
  newNode->data = data;
  newNode->next = st->top;
  st->top = newNode;
  st->size++;
  return 1;
}

void *stackPop(Stack s) {
  if (s == NULL || stackIsEmpty(s))
    return NULL;
  stack *st = (stack *)s;
  Node *nodeToPop = st->top;
  void *data = nodeToPop->data;
  st->top = nodeToPop->next;
  free(nodeToPop);
  st->size--;
  return data;
}

void *stackTop(Stack s) {
  if (s == NULL || stackIsEmpty(s))
    return NULL;
  stack *st = (stack *)s;
  return st->top->data;
}

int stackGetSize(Stack s) {
  if (s == NULL)
    return -1;
  stack *st = (stack *)s;
  return st->size;
}
