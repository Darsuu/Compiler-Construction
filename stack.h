#ifndef STACK_H
#define STACK_H

#include "linkedlist.h"
#include "stackDef.h"

 // Stack is a pointer to a struct stack

Stack* newStack();
// Returns a pointer to a new stack. Returns NULL if memory allocation fails

void push(Stack* mainStack, NODE element);
// Pushes element onto stack. Returns false if memory allocation fails

NODE top(Stack* mainStack);
// Returns the top element. Returns NULL if stack is empty

void pop(Stack* mainStack);
// Pops the top element and returns true. Returns false if stack is empty

int reachEnd(Stack* mainStack);
// returns 1 if empty. 0 otherwise

void pushDerivation(Stack* mainStack, NODE rules);

// HELPER FUNCTION
void printStack(Stack* mainStack);

#endif