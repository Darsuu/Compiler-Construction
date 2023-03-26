#include "stack.h"
#include "Nlinkedlist.h"
#include "grammar.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

Stack* newStack()
{
    Stack* mainStack = (Stack*) malloc(sizeof(Stack));
    mainStack->list1 = createNewList();
    return mainStack;
}

void push(Stack* mainStack, NODE element)
{
    // printNT(element->val.nt_val);
    LIST temp = mainStack->list1;
    insertNodeIntoList(element, temp);
}

NODE top(Stack* mainStack) 
{
    LIST ll = mainStack->list1;
    NODE temp = ll->head;
    return temp;
}

void pop(Stack* mainStack)
{
    LIST ll = mainStack->list1;
    removeFirst(ll);
}

int reachEnd(Stack* mainStack)
{
    if(mainStack->list1->head != NULL) return 0;
    else return 1;
}

void pushDerivation(Stack* mainStack, NODE rules)
{
    Stack* temp = newStack();
    while(rules != NULL)
    {
        push(temp, rules);
        rules = rules->next;
    }
    while(!reachEnd(temp))
    {
        NODE ins = top(temp);
        pop(temp);
        push(mainStack, ins);
    }
}


// HELPER FUNCTIONx
void printStack(Stack* mainStack)
{
    while(!reachEnd(mainStack))
    {
        NODE temp = top(mainStack);
        
        if(temp->tnt == 1)
        {
            printNT(temp->val.nt_val);
            printf("\n");
        }
        else
        {
            printT(temp->val.t_val);
            printf("\n");
        }
        pop(mainStack);
    }
}
