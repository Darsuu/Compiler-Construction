//your stack is not making sense to me
//stack should be a linkedlist of nodes, and unlike rule, iska addition and deletion is at the head and not the tail, so can't use the same linkedlist struct
#include "stack.h"
#include "linkedlist.h"
#include "grammar.h"
#include <stdio.h>
#include <stdlib.h>

Stack* newStack()
{
    RULE ll = createNewRule(0, -1);
    Stack* mainStack = (Stack*) malloc(sizeof(Stack));
    mainStack->ll = ll;
    mainStack->end = createNewTerm(ENDOFFILE,0,0);
    return mainStack;
}

void push(Stack* mainStack, NODE element)
{
    RULE ll = mainStack->ll;
    insertNodeIntoRule(element, ll);
}

NODE top(Stack* mainStack) 
{
    RULE ll = mainStack->ll;
    NODE temp = ll->head;
    if(temp==NULL) return mainStack->end;
    return temp;
}

void pop(Stack* mainStack)
{
    RULE ll = mainStack->ll;
    removeFirstNode(ll);
}

int reachEnd(Stack* mainStack)
{
    if(mainStack->ll->head->next != NULL) return 0;
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

void printStack(Stack* mainStack)
{
    while(!reachEnd(mainStack))
    {
        NODE temp = top(mainStack);
        pop(mainStack);
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
    }
    // printT(mainStack->end->val.t_val);
}
