/*
Group No. : 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/

#ifndef PARSER_H
#define PARSER_H
#include "lexerDef.h"
#include "linkedlist.h"

void automaticFirsts();
void automaticFollows();
void computeFirsts();
void computeFollows();

void createParseTable();
void parseInputSourceCode();
void printFirsts(void);
void printFollows(void);
void printParseTable();
NODE* getFirsts();
NODE* getFollows();
int** getParseTable();
void runParser();

#endif