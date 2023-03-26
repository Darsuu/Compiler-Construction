/*
Group No. : 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/

#include "stack.h"
#include "linkedlist.h"
#include "grammar.h"
#include "grammarDef.h"
#include "lexerDef.h"
#include <stdio.h>
#include <stdlib.h>

LIST createNewList()
{
    LIST ll = (LIST) malloc(sizeof(linked_list));
    ll->count = 0;
    ll->head = NULL;
    return ll;
}

NODE createNewNode(token t, NT nt, int tnt)
{
    NODE temp = (NODE) malloc(sizeof(node));
    if(temp->tnt == 1)
    {
        temp->val.nt_val = nt;
    }
    else temp->val.t_val = t;
    temp->tnt = tnt;
    temp->next = NULL;
    return temp;
}

void insertNodeIntoList(NODE node, LIST list)
{
    list->count++;
    if(list->head == NULL)
    {
        list->head = node;
        return;
    }
    else
    {
        NODE temp = list->head;
        list->head = node;
        node->next = temp;
    }
}

void removeFirst(LIST list)
{
    if(list->count == 1)
    {
        NODE temp = list->head;
        //free(temp);
        list->head = NULL;
    }
    else
    {
        NODE temp = list->head->next;
        NODE remove = list->head;
        //free(remove);
        list->head = temp;
    }
    list->count--;
}
