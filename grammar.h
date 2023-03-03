#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "grammarDef.h"
#include "linkedlist.h"

extern RULE** table;

void printNT(NT term);

void generateFirst(RULE** table); 

void printFirst(void);

void calculateFollow(RULE* arr,RULE** table, int index);
void generateFollow(RULE** table);


void buildGrammar();

#endif