#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <string.h>
#include "lexerDef.h" 

FILE* getStream(FILE *fp);
tokenInfo* getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);
void printToken(tokenInfo* currToken);
void flipBuffer(char c);
void runLexer(void);
void printT(token token);

#endif