//

#ifndef STACK_H
#define STACK_H

typedef void *ELEMENT;
typedef void *Stack;

// Function Prototypes

Stack stackInit(); // Function to initialize the stack

bool stackIsEmpty(Stack *p); // Function to check if the stack is empty

void stackIsFull(Stack *p, int len); // Function to check if the stack is full

int stackLen(STACK *p); // Function to get stack size

int stackPush(STACK *p); // Function to push an element onto the stack

int stackPop(STACK *p); // Function to pop an element from the stack

#endif // STACK_H
