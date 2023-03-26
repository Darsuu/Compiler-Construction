/*
Group No. : 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/
#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <string.h>
#include "lexerDef.h" 

FILE* getStream(FILE *fp);
tokenInfo* getNextToken();
void initializeLexerOnce();
void removeComments(char *testcaseFile, char *cleanFile);
tokenInfo* runLexerForParser(char* testfile, int size);
void printToken(tokenInfo* currToken);
void runLexer(char* testfile, int size);
void printT(token token);
void fprintT(FILE* fp, token token);

#endif