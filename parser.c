/*
ID: 2020A7PS1214P   Name: Darshan Abhaykumar
ID: 2020A7PS0970P   Name: Debjit Kar
ID:2020A7PS0986P    Name: Nidhish Parekh
*/

#include "grammar.h"
#include "parser.h"
#include "stack.h"
#include "lexer.h"
#include "linkedlist.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
 

int** parseTable;
NODE* firsts;
NODE* follows; 

void createParseTable(){
    parseTable = (int**) malloc(NT_COUNT*sizeof(int*));

    for(int i = 0; i < NT_COUNT; i++){
        parseTable[i] = (int*) malloc(TOKEN_COUNT*sizeof(int));
    }

    for(int i = 0; i < NT_COUNT; i++){
        for(int j = 0; j < TOKEN_COUNT; j++){
            parseTable[i][j] = -1;
        }
    }
    
    NT nt;
    NODE rhs;//left most term of rhs of rule
    NODE currNode;//traverses first of rhs or follow of lhs
    int ep = 1;

    for(int i = 0; i < NT_COUNT; i++){
        for(int j = 0; j < TOKEN_COUNT; j++){
            if(table[i][j] == NULL) break;

            rhs = table[i][j]->head->next;
            while(ep && rhs!=NULL){ 
                ep = 0;//epsilon flag
                
                if(rhs->tnt){                                   //if term is nt
                    nt = rhs->val.nt_val;
                    currNode = firsts[nt];
                    
                    do{
                        if(currNode->val.t_val == EPSILON) ep = 1;      //set epsilon flag
                        parseTable[i][currNode->val.t_val] = j;
                        currNode = currNode->next;
                        
                    }
                    while(currNode!=NULL);                              //end of first(nt)
                }
                else{   
                    if(rhs->val.t_val == EPSILON) ep = 1;
                    parseTable[i][rhs->val.t_val] = j;
                }
                rhs = rhs->next;
            }

            if(ep){                                         //follow of lhs NT 
                currNode = follows[i];
                do{ 
                    parseTable[i][currNode->val.t_val] = j;
                    currNode = currNode->next;
                }
                while(currNode!=NULL);  
                
            }
            ep = 1;
        }
    }

}

void printParseTable(){
    for(int i = 0; i < NT_COUNT; i++){
        for(int j = 0; j < TOKEN_COUNT; j++){
            if(parseTable[i][j]!=-1) printf("%d ", parseTable[i][j]);
            if(j == TOKEN_COUNT-1) printf("\n");
        }
    }
}

void parseInputSourceCode(char *testcaseFile, int** parseTable){
    int rule_no = 0;
    FILE * fp = fopen(testcaseFile,"r");
    fp = getStream(fp);
    Stack* mainStack = newStack(); 
    token placeholder;
    push(mainStack, createNewTerm(ENDOFFILE,0,0));
    push(mainStack, createNewTerm(placeholder, program, 1));
    int tek = 0;
    tokenInfo* readToken = getNextToken();
    tek++;
    TREENODE t1 = initTree();
    if(readToken == ENDOFFILE)
    {
        printf("File is empty\n");
    }
    while(!reachEnd(mainStack))
    {   
        printf("%d ",readToken->token); printT(readToken->token); printf("\n");  
        fflush(stdout);

        // printToken(readToken);
        // printf("\n");
        // fflush(stdout);
        
        NODE temp = top(mainStack);

        pop(mainStack);
        if(temp->tnt == 0)
        {
            // printf("Working\n");
            // fflush(stdout);            
            printT(temp->val.t_val); printf("\n");
            if(temp->val.t_val != readToken->token)
            {
                if(temp->val.t_val == EPSILON)
                {
                    printToken(readToken);
                    temp = top(mainStack);
                    pop(mainStack);
                    continue;
                }
                if(readToken->token == ENDOFFILE)
                {
                    printf("ERROR: Input consumed but Stack not empty\n");
                    break; // CHECK
                } 
                else
                {
                    printf("ERROR: Terminal Mismatch\n");
                    break; // CHECK
                }  
                readToken = getNextToken();
                // CHECK FOR NULL 
                continue;
            }
            else // TOP OF STACK MATCHES WITH TOKEN
            {
                // temp = top(mainStack);
                // pop(mainStack);
                // readToken = getNextToken();
                if(reachEnd(mainStack))
                {
                    printf("Finished parsing\n");
                }
                continue;
            }
        }
        else if(temp->tnt==1){
            printNT(temp->val.nt_val);
            printf("\n");
            fflush(stdout);
            

            int x = parseTable[temp->val.nt_val][readToken->token];

            printf("%d",x);
            fflush(stdout);
            if(x!=-1){
                printf("test");
                fflush(stdout);
                pushDerivation(mainStack,table[temp->val.nt_val][x]);
                readToken = getNextToken();

            }
            else{
                printf("ERROR: Syntactic error\n");
            }
        }
        else{
            printf("ERROR: Stack emptied before input consumed\n");
        }


        
        
    }


}

void computeFirsts(){
    firsts = (NODE*) malloc(NT_COUNT * sizeof(NODE));
    for(int i = 0; i<NT_COUNT; i++)
    {
        firsts[i] = (NODE) malloc(RULE_COUNT * sizeof(node));
    }

    NODE temp = createNewTerm(FOR, 0, 0);
    addTermToSet(temp, firsts[iterativeStmt]);
    temp = createNewTerm(WHILE, 0, 0);
    addTermToSet(temp,firsts[iterativeStmt]);

     temp = createNewTerm(DEFAULT, 0, 0);
    addTermToSet(temp,firsts[default_stmt]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[default_stmt]);

     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[value]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[value]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[value]);

     temp = createNewTerm(CASE, 0, 0);
    addTermToSet(temp,firsts[caseStmts]);

     temp = createNewTerm(CASE, 0, 0);
    addTermToSet(temp,firsts[caseStmts2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[caseStmts2]);

     temp = createNewTerm(SWITCH, 0, 0);
    addTermToSet(temp,firsts[conditionalStmt]);

     temp = createNewTerm(DECLARE, 0, 0);
    addTermToSet(temp,firsts[declareStmt]);

     temp = createNewTerm(LT, 0, 0);
    addTermToSet(temp,firsts[relationalOp]);
     temp = createNewTerm(LE, 0, 0);
    addTermToSet(temp,firsts[relationalOp]);
     temp = createNewTerm(GT, 0, 0);
    addTermToSet(temp,firsts[relationalOp]);
     temp = createNewTerm(GE, 0, 0);
    addTermToSet(temp,firsts[relationalOp]);
     temp = createNewTerm(EQ, 0, 0);
    addTermToSet(temp,firsts[relationalOp]);
     temp = createNewTerm(NE, 0, 0);
    addTermToSet(temp,firsts[relationalOp]);

     temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,firsts[logicalOp]);
     temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,firsts[logicalOp]);

     temp = createNewTerm(LT, 0, 0);
    addTermToSet(temp,firsts[Term8]);
     temp = createNewTerm(LE, 0, 0);
    addTermToSet(temp,firsts[Term8]);
     temp = createNewTerm(GT, 0, 0);
    addTermToSet(temp,firsts[Term8]);
     temp = createNewTerm(GE, 0, 0);
    addTermToSet(temp,firsts[Term8]);
     temp = createNewTerm(EQ, 0, 0);
    addTermToSet(temp,firsts[Term8]);
     temp = createNewTerm(NE, 0, 0);
    addTermToSet(temp,firsts[Term8]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[Term8]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[AnyTerm]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[AnyTerm]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[AnyTerm]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[AnyTerm]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[AnyTerm]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[AnyTerm]);

     temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,firsts[Term7]);
     temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,firsts[Term7]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[Term7]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[abExpr]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[abExpr]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[abExpr]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[abExpr]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[abExpr]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[abExpr]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[uni_op]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[uni_op]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[new_NT]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[new_NT]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[new_NT]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[new_NT]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[U]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[U]);

     temp = createNewTerm(MUL, 0, 0);
    addTermToSet(temp,firsts[high_op]);
     temp = createNewTerm(DIV, 0, 0);
    addTermToSet(temp,firsts[high_op]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[low_op]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[low_op]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[factor]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[factor]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[factor]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[factor]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[factor]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[factor]);

     temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[factor2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[factor2]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[exprIndex]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[arrExpr]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[arrExpr]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[arrExpr]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[arrExpr]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[arrExpr]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[arrExpr]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[arrExpr2]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[arrExpr2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[arrExpr2]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[arrTerm]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[arrTerm]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[arrTerm]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[arrTerm]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[arrTerm]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[arrTerm]);

     temp = createNewTerm(MUL, 0, 0);
    addTermToSet(temp,firsts[arrTerm2]);
     temp = createNewTerm(DIV, 0, 0);
    addTermToSet(temp,firsts[arrTerm2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[arrTerm2]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[arrFactor]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[arrFactor]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[arrFactor]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[arrFactor]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[arrFactor]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[arrFactor]);

     temp = createNewTerm(MUL, 0, 0);
    addTermToSet(temp,firsts[term2]);
     temp = createNewTerm(DIV, 0, 0);
    addTermToSet(temp,firsts[term2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[term2]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[term]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[term]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[term]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[term]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[term]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[term]);

     temp = createNewTerm(MUL, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr2]);
     temp = createNewTerm(DIV, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr2]);

     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[arithmeticExpr]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(BO, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[expression]);
     temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[expression]);

     temp = createNewTerm(COMMA, 0, 0);
    addTermToSet(temp,firsts[idList2]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[idList2]);

     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[idList]);

     temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[optional]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[optional]);

     temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[moduleReuseStmt]);
     temp = createNewTerm(USE, 0, 0);
    addTermToSet(temp,firsts[moduleReuseStmt]);

     temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[lvalueARRStmt]);
    
     temp = createNewTerm(ASSIGNOP, 0, 0);
    addTermToSet(temp,firsts[lvalueIDStmt]);

     temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[sign]);
     temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[sign]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[sign]);

     temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[whichStmt]);
     temp = createNewTerm(ASSIGNOP, 0, 0);
    addTermToSet(temp,firsts[whichStmt]);

     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[assignmentStmt]);

     temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[simpleStmt]);
     temp = createNewTerm(USE, 0, 0);
    addTermToSet(temp,firsts[simpleStmt]);
     temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[simpleStmt]);

     temp = createNewTerm(DECLARE, 0, 0);
    addTermToSet(temp,firsts[program]);
     temp = createNewTerm(DEF, 0, 0);
    addTermToSet(temp,firsts[program]);
     temp = createNewTerm(DRIVERDEF, 0, 0);
    addTermToSet(temp,firsts[program]);

     temp = createNewTerm(DECLARE, 0, 0);
    addTermToSet(temp,firsts[moduleDeclarations]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[moduleDeclarations]);

     temp = createNewTerm(DECLARE, 0, 0);
    addTermToSet(temp,firsts[moduleDeclaration]);

     temp = createNewTerm(DEF, 0, 0);
    addTermToSet(temp,firsts[otherModules]);
     temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[otherModules]);

    temp = createNewTerm(DRIVERDEF, 0, 0);
    addTermToSet(temp,firsts[driverModule]);

    temp = createNewTerm(DEF, 0, 0);
    addTermToSet(temp,firsts[module]);

    temp = createNewTerm(RETURNS, 0, 0);
    addTermToSet(temp,firsts[ret]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[ret]);

    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[input_plist]);

    temp = createNewTerm(COMMA, 0, 0);
    addTermToSet(temp,firsts[input_plist2]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[input_plist2]);

    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[output_plist]);

    temp = createNewTerm(COMMA, 0, 0);
    addTermToSet(temp,firsts[output_plist2]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[output_plist2]);

    temp = createNewTerm(INTEGER, 0, 0);
    addTermToSet(temp,firsts[dataType]);
    temp = createNewTerm(REAL, 0, 0);
    addTermToSet(temp,firsts[dataType]);
    temp = createNewTerm(BOOLEAN, 0, 0);
    addTermToSet(temp,firsts[dataType]);
    temp = createNewTerm(ARRAY, 0, 0);
    addTermToSet(temp,firsts[dataType]);

    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[arr_range]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[arr_range]);
    temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[arr_range]);
    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[arr_range]);

    temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[num_or_id]);
    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[num_or_id]);

    temp = createNewTerm(INTEGER, 0, 0);
    addTermToSet(temp,firsts[type]);
    temp = createNewTerm(REAL, 0, 0);
    addTermToSet(temp,firsts[type]);
    temp = createNewTerm(BOOLEAN, 0, 0);
    addTermToSet(temp,firsts[type]);

    temp = createNewTerm(START, 0, 0);
    addTermToSet(temp,firsts[moduleDef]);

    temp = createNewTerm(GET_VALUE, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(PRINT, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(USE, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(DECLARE, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(SWITCH, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(FOR, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(WHILE, 0, 0);
    addTermToSet(temp,firsts[statements]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[statements]);

    temp = createNewTerm(GET_VALUE, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(PRINT, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(USE, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(DECLARE, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(SWITCH, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(FOR, 0, 0);
    addTermToSet(temp,firsts[statement]);
    temp = createNewTerm(WHILE, 0, 0);
    addTermToSet(temp,firsts[statement]);

    temp = createNewTerm(GET_VALUE, 0, 0);
    addTermToSet(temp,firsts[ioStmt]);
    temp = createNewTerm(PRINT, 0, 0);
    addTermToSet(temp,firsts[ioStmt]);

    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[print_var]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[print_var]);
    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[print_var]);
    temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[print_var]);
    temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[print_var]);
    temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[print_var]);
    temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[print_var]);

    temp = createNewTerm(SQBO, 0, 0);
    addTermToSet(temp,firsts[which_ID]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[which_ID]);

    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[for_range]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[for_range]);

    temp = createNewTerm(ID, 0, 0);
    addTermToSet(temp,firsts[con_var]);
    temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[con_var]);
    temp = createNewTerm(RNUM, 0, 0);
    addTermToSet(temp,firsts[con_var]);

    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[for_sign]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[for_sign]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[for_sign]);
    
    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[for_index]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[for_index]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[for_index]);

    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,firsts[arr_index]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,firsts[arr_index]);
    temp = createNewTerm(EPSILON, 0, 0);
    addTermToSet(temp,firsts[arr_index]);

    temp = createNewTerm(NUM, 0, 0);
    addTermToSet(temp,firsts[for_index2]);

    temp = createNewTerm(TRUE, 0, 0);
    addTermToSet(temp,firsts[boolVal]);
    temp = createNewTerm(FALSE, 0, 0);
    addTermToSet(temp,firsts[boolVal]);

}

void computeFollows(){
    follows = (NODE*) malloc(NT_COUNT * sizeof(NODE));
    for(int i = 0; i<NT_COUNT; i++)
    {
        follows[i] = (NODE) malloc(RULE_COUNT * sizeof(node));
    }

    NODE temp = createNewTerm(ENDOFFILE, 0, 0);
    addTermToSet(temp,follows[program]);

    temp = createNewTerm(DEF, 0, 0);
    addTermToSet(temp,follows[moduleDeclarations]);
    temp = createNewTerm(DRIVERDEF, 0, 0);
    addTermToSet(temp,follows[moduleDeclarations]);
    temp = createNewTerm(ENDOFFILE, 0, 0);
    addTermToSet(temp,follows[moduleDeclarations]);

    temp = createNewTerm(DRIVERDEF, 0, 0);
    addTermToSet(temp,follows[otherModules]);
    temp = createNewTerm(ENDOFFILE, 0, 0);
    addTermToSet(temp,follows[otherModules]);

    temp = createNewTerm(START, 0, 0);
    addTermToSet(temp,follows[ret]);

    temp = createNewTerm(SQBC, 0, 0);
    addTermToSet(temp,follows[input_plist]);

    temp = createNewTerm(SQBC, 0, 0);
    addTermToSet(temp,follows[input_plist2]);

    temp = createNewTerm(SQBC, 0, 0);
    addTermToSet(temp,follows[output_plist]);

    temp = createNewTerm(SQBC, 0, 0);
    addTermToSet(temp,follows[output_plist2]);

    temp = createNewTerm(END, 0, 0);
    addTermToSet(temp,follows[statements]);
    temp = createNewTerm(BREAK, 0, 0);
    addTermToSet(temp,follows[statements]);

    
    temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,follows[Term8]);
    temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,follows[Term8]);
    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[Term8]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[Term8]);

    temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,follows[AnyTerm]);
    temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,follows[AnyTerm]);
    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[AnyTerm]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[AnyTerm]);

    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[Term7]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[Term7]);

    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[abExpr]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[abExpr]);

    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[expression]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[expression]);

    temp = createNewTerm(LT, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(LE, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(GT, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(GE, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(NE, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(EQ, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr2]);

    temp = createNewTerm(LT, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(LE, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(GT, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(GE, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(NE, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(EQ, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[arithmeticExpr]);

    temp = createNewTerm(LT, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(LE, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(GT, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(GE, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(NE, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(EQ, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,follows[term]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,follows[term]);

    temp = createNewTerm(LT, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(LE, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(GT, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(GE, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(NE, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(EQ, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(AND, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(OR, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(SEMICOL, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(BC, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(PLUS, 0, 0);
    addTermToSet(temp,follows[term2]);
    temp = createNewTerm(MINUS, 0, 0);
    addTermToSet(temp,follows[term2]);

    temp = createNewTerm(END, 0, 0);
    addTermToSet(temp,follows[caseStmts]);
    temp = createNewTerm(DEFAULT, 0, 0);
    addTermToSet(temp,follows[caseStmts]);
    
    temp = createNewTerm(END, 0, 0);
    addTermToSet(temp,follows[caseStmts2]);
    temp = createNewTerm(DEFAULT, 0, 0);
    addTermToSet(temp,follows[caseStmts2]);

    temp = createNewTerm(END, 0, 0);
    addTermToSet(temp,follows[default_stmt]);

}

NODE* getFollows(void){
    return follows;
}

NODE* getFirsts(void){
    return firsts;
}

int** getParseTable(){
    return parseTable;
}

void printFirsts(void)
{
    for(int i = 0;i < NT_COUNT; i++)
    {
        if(firsts[i] != NULL)
        {
            NODE temp = firsts[i];
            temp = temp->next;
            while(temp!=NULL)
            {
                printf("%d ", temp->val.t_val);
                temp = temp->next;
            }
        }
        printf("\n");
    }
        
}

void printFollows(void)
{
    for(int i = 0;i < NT_COUNT; i++)
    {
        if(follows[i] != NULL)
        {
            NODE temp = follows[i];
            temp = temp->next;
            while(temp!=NULL)
            {
                printf("%d ", temp->val.t_val);
                temp = temp->next;
            }
        }
        printf("\n");
    }
        
}

void runParser()
{
    // FILE * fp = fopen(,"r");
    // fp = getStream(fp);
    // buildGrammar();
    // computeFirsts();
    // computeFollows();
    // createParseTable();
    // parseInputSourceCode("input.txt", getParseTable());
    // Stack* mainStack = newStack();

    // NODE temp2 = createNewTerm(10, 10, 0);
    // printNT(temp2->tnt);
    // push(mainStack, createNewTerm(0, 0, 10));
    // push(mainStack, createNewTerm( 0, 0, 0));
    // printf("%d\n", mainStack->list1->count);
    // push(mainStack, createNewTerm( 0, 0, 0));
    // printStack(mainStack);

    
}