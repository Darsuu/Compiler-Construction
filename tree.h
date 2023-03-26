#ifndef TREE_H
#define TREE_H
#include "treeDef.h"

TREENODE initTree();
void leftmostDerive(NODE deriv, TREENODE t1);
void runTree(char* outputfile);
void printTree(TREENODE node, int level, FILE* fp1);
void printParseTree(TREENODE t1, char* outfile);

#endif