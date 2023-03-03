#ifndef TREE_H
#define TREE_H
#include "treeDef.h"

TREENODE initTree();
void leftmostDerive(NODE deriv, TREENODE t1);
void runTree(void);
void printTree(TREENODE t1);
void printParseTree(TREENODE t1, char* outfile);

#endif