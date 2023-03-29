#include "lexerDef.h"
#include "grammar.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

RULE createNewRule(NT nt_val, int n)
{
    RULE rule = (RULE) malloc(sizeof(linked_list));
    NODE lhs = (NODE) malloc(sizeof(node));
    lhs->tnt = 1;
    lhs->val.nt_val = nt_val;
    lhs->next = NULL;

    rule->rule_no = n;
    rule->nt_val = nt_val;
    rule->head = lhs;
    return rule;
}
// This function allocates memory for a new RULE and returns a pointer to it.
// The RULE is empty and the count is set to 0.

NODE createNewTerm(token t_val, NT nt_val, int n)
{
    NODE temp = (NODE) malloc(sizeof(node));
    if(n){
        temp->val.nt_val = nt_val;
        temp->tnt = 1;
    }
    else{
        temp->val.t_val = t_val;
        temp->tnt = 0;
    }
    temp->next = NULL;
    return temp;
}
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertNodeIntoRule(NODE node, RULE rule)
{
    if(rule->head == NULL)
    {
        rule->head = node;
        return;
    }
    else
    {
        NODE temp = rule->head;
        rule->head = node;
        node->next = temp;
    }
}
// This function inserts a node at the beginning of the RULE.

void removeFirstNode(RULE rule)
{
    NODE temp = rule->head->next;
    NODE remove = rule->head;
    free(remove); 
    rule->head = temp;
}
// This function removes the first node from the RULE.

void addTermToRule(RULE rule, token t_val, NT nt_val, int tnt){
    NODE node = createNewTerm(t_val,nt_val,tnt);
    NODE temp = rule->head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = node;
}
// This function inserts a node at the end of the RULE.

// void destroyRULE(RULE rule)
// {
//     if(rule->count == -1)
//     {
//         free(rule);
//         return;
//     }
//     NODE arr[(rule->count)+1];
//     int i = 0;
//     NODE temp = rule->head;
//     while(temp != NULL)
//     {
//         arr[i++] = temp;
//         temp = temp->next;
//     }
//     while(--i>=0) free(arr[i]);
//     free(rule);
// }

void printRule(RULE rule){
    NODE temp = rule->head;
    printNT(temp->val.nt_val);
    temp = temp->next;
    printf(" --> ");

    while(temp!=NULL){
        if(temp->tnt) printNT(temp->val.nt_val);
        else printT(temp->val.t_val);

        temp = temp->next;
    }
    printf("\n");

}

NODE copyTerm(NODE node)
{
    NODE temp = (NODE) malloc(sizeof(node));
    if(node->tnt){
        temp->val.nt_val = node->val.nt_val;
        temp->tnt = 1;
    }
    else{
        temp->val.t_val = node->val.t_val;
        temp->tnt = 0;
    }
    temp->next = NULL;
    return temp;
}

void addTermToSet(NODE node, NODE set){
    if(set == NULL)
    {
        set->next = NULL;
        set->val.t_val = node->val.t_val;
    } 
    else{
        while(set->next!=NULL)
        {
            if(set->val.t_val == node->val.t_val) return;
            set = set->next;
        }
        if(set->val.t_val == node->val.t_val) return;
        set->next=node;
    }

}