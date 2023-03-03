#include <stdio.h>
#include <stdlib.h>
#include "grammar.h"
#include "parser.h"
#include "linkedlist.h"
#include "grammarDef.h"

int main(){
	firsts = (NODE*) malloc(NT_COUNT * sizeof(NODE));
    for(int i = 0; i<NT_COUNT; i++)
    {
        firsts[i] = (NODE) malloc(RULE_COUNT * sizeof(node));
    }

    NODE temp = createNewTerm(/*terminal in first*/, 0, 0);
    addTermToSet(temp,firsts[/*jiska first set ban raha hai*/]);

}