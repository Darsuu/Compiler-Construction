#include "parser.h"
#include "lexer.h"
#include "grammar.h"
#include "linkedlist.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	// FILE * fp = fopen(,"r");
    // fp = getStream(fp);
    // buildGrammar();
    // computeFirsts();
    // computeFollows();
    // createParseTable();
    // parseInputSourceCode("input.txt", getParseTable());
    Stack* mainStack = newStack();
    
    push(mainStack, createNewTerm( 0, 0, 0));
    push(mainStack, createNewTerm( 0, 0, 0));
    push(mainStack, createNewTerm( 0, 0, 0));
    push(mainStack, createNewTerm( 0, 0, 0));
    printStack(mainStack);
}

