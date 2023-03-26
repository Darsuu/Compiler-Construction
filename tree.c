#include "treeDef.h"
#include "lexer.h"
#include "grammar.h"
#include <stdlib.h>


TREENODE initTree()
{
    TREENODE temp = (TREENODE) malloc(sizeof(struct TreeNode));
    temp->firstChild = NULL;
    temp->nextSibling = NULL;   
    temp->parent = NULL;
    temp->lexeme = NULL;
    temp->line_no = 0;
    temp->tnt = 1; // CHECK
    temp->val.nt_val = program; // CHECK
    return temp;    
}

void leftmostDerive(NODE deriv, TREENODE t1)
{
    TREENODE curr = t1;
    TREENODE parent;
    if(deriv != NULL)
    {
        while(curr->firstChild != NULL) // LOOP WHILE CHILD IS TERMINAL
        {   
            parent = curr;
            curr = curr->firstChild;
        } 
        
        if(curr->tnt == 0) // LAST CHILD IS TERMINAL
        {
            
            while(curr->nextSibling != NULL && curr->tnt == 0) // LOOP WHILE SIBLING IS TERMINAL AND NOT THE END
            {
                curr = curr->nextSibling;
            }  
            if(curr->tnt == 0)
            {
                leftmostDerive(deriv, parent->nextSibling); // LAST CHILD IS TERMINAL THEN LOOK AT UNCLE
                return;
            } 
            else 
            {
                leftmostDerive(deriv, curr); // RECURSIVELY ADD DERIVATION TO CURR
                return;
            }
        }
        else
        {
            TREENODE temp = (TREENODE) malloc(sizeof(struct TreeNode));
            temp->firstChild = NULL;
            temp->nextSibling = NULL;   
            temp->parent = curr;
            temp->tnt = deriv->tnt;
            if(temp->tnt == 0) temp->val.t_val = deriv->val.t_val;
            else temp->val.nt_val = deriv->val.nt_val;
            curr->firstChild = temp;
            curr = curr->firstChild;
            deriv = deriv->next;
        }
        
    }
    while(deriv!=NULL)
    {
        TREENODE temp = (TREENODE) malloc(sizeof(struct TreeNode));
        temp->firstChild = NULL;
        temp->nextSibling = NULL;   
        temp->parent = NULL;
        temp->tnt = deriv->tnt;
        if(temp->tnt == 0) temp->val.t_val = deriv->val.t_val;
        else temp->val.nt_val = deriv->val.nt_val;
        curr->nextSibling = temp;
        curr = curr->nextSibling;
        deriv = deriv->next;
    }
}

void printParseTree(TREENODE t1, char* outfile)
{
//     if(t1 == NULL) return;
//     if(t1->firstChild!=NULL)
//     {
//         inOrderTraversal(t1->firstChild);
//     }
//     if(t1->parent != NULL)
//     [
//         if(t1->parent->tnt == 0) printT(t1->parent->val.t_val);
//         else printNT(t1->parent->val.nt_val);
//     ]
//     else printf("ROOT");
//     inOrderTraversal(temp);
//     if(temp!=NULL)
//     {
        
//     }
//     if(temp != NULL) temp = temp->nextSibling;
//     while(temp!=NULL)
//     {
//         inOrderTraversal(temp);
//         temp = temp->nextSibling;
//     }
}

// HELPER FUNCTION
void printTree(TREENODE node, int level, FILE* fp)
{
    while (node != NULL)
    {
        for (int i = 0; i < level; i++)
        {
            fprintf(fp, "\t");
        } 
        fprintf(fp, "Level %d Node -> ", level);
        if(node->tnt == 0) fprintT(fp, node->val.t_val);
        else fprintNT(fp, node->val.nt_val);
        fprintf(fp, "\n");

        if (node->firstChild != NULL)
        {
            for (int i = 0; i < level; i++) fprintf(fp, "\t");
            fprintf(fp, "Children: \n");
            printTree(node->firstChild, level + 1, fp);
        }
        node = node->nextSibling;
    }
}


void runTree(char* outputfile)
{
    TREENODE t1 = initTree();
    RULE temp = createNewRule(program, 0);
    addTermToRule(temp, 0, 0, 1);
    addTermToRule(temp, 0, 0, 0);
    addTermToRule(temp, 0, 1, 1);
    RULE temp2 = createNewRule(moduleDeclarations, 1);
    addTermToRule(temp2, 0, 0, 1);
    addTermToRule(temp2, 0, 0, 0);
    addTermToRule(temp2, 0, 0, 0);
    leftmostDerive(temp->head->next, t1);
    leftmostDerive(temp2->head->next, t1);
    FILE* fp1 = fopen(outputfile, "w");
    printTree(t1,0, fp1);
    fclose(fp1);
}
