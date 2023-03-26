#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "grammarDef.h"
#include "linkedlist.h"
#include "stdio.h"

extern RULE** table;

void printNT(NT term);
void fprintNT(FILE* fp, NT term);
void generateFirst(RULE** table); 
void printFirst(void);
void calculateFollow(RULE* arr,RULE** table, int index);
void generateFollow(RULE** table);
void runGrammar();
void buildGrammar();

#endif