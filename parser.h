#ifndef PARSER_H
#define PARSER_H
#include "lexerDef.h"
#include "linkedlist.h"

extern int** parseTable;
extern NODE* firsts;
extern NODE* follows;

void computeFirsts();
void computeFollows();

void createParseTable();
void parseInputSourceCode();
void printFirsts(void);
void printFollows(void);
void printParseTable();

#endif