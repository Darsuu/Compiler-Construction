#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "lexerDef.h"
#include "grammarDef.h"

struct node
{
    int tnt;//0 is terminal i.e. token and 1 is non terminal
    union {
        token t_val;
        NT nt_val;
    } val;
    struct node *next;
};

typedef struct node node;
typedef node * NODE;


struct linked_list
{
    int rule_no;
    NT nt_val;
    NODE head;
    
};
typedef struct linked_list linked_list;
typedef linked_list * RULE;

RULE createNewRule(NT nt_val, int n);
// This function allocates memory for a new list and returns a pointer to it.

NODE createNewTerm(token t_val, NT nt_val, int n);
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertNodeIntoRule(NODE node, RULE rule);
// This function inserts a node at the beginning of the list.

void removeFirstNode(RULE rule);
// This function removes the first node from the list.

// void insertNodeAtEnd(NODE node, LIST list); // Not required for stack. Required for Queue
// This function inserts a node at the end of the list.

void destroyList(RULE rule);

void addTermToRule(RULE rule, token t_val, NT nt_val, int tnt);
//function adds term to the rule at right

void printRule(RULE rule);
void addTermToSet(NODE node, NODE set);

#endif