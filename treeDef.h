#ifndef TREEDEF_H
#define TREEDEF_H
#include "lexerDef.h"
#include "linkedlist.h"
#include "grammarDef.h"


struct TreeNode
{
    int tnt; // 0 is terminal and 1 is non terminal
    char* lexeme;
    int line_no;

    union {
        token t_val;
        NT nt_val;
    } val;
    struct TreeNode* firstChild;
    struct TreeNode* nextSibling;    
    struct TreeNode* parent;

};
typedef struct TreeNode* TREENODE;

#endif