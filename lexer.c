/*
Group No. : 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/

/*
    This file is being used by the driver file to simulate the lexer.
    The lexer implements a twin buffer for efficient convertion of char
    stream into a token stream. The runLexer() will get called by the driver which
    tokensies the entire file. The getNextToken() will be used by the parses for 
    getting the token sequentially

*/

#ifndef LEXER_C
#define LEXER_C
#include "lexerDef.h"
#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int line, b_id, beg_id, forward, begin;
int BufferSize;
int charCount = 1, first_load = 1, spill = 0;
int switched = 0;
buffer b;
HTableEntry ht[MODULO];
tokenInfo* t;
FILE* fp;
char *lexeme;

void freeData();
void initializeLexerOnce()
{
    for(int i=0;i<MODULO;i++) ht[i].valid = 0;
    initTable(ht);
}

void initialize(FILE *fp)
{
    b.one = (char *) malloc(BufferSize*sizeof(char));
    b.two = (char *) malloc(BufferSize*sizeof(char));
    b_id = 0;
    line = 1;
    forward = 0;
    begin = 0;
    fread(b.one,sizeof(char),BufferSize,fp);
}

//if no more to read, buffer unchanged
FILE* getStream(FILE *fp){
    if(fp == NULL){
        printf("File pointer is null\n");
        return NULL;
    }
    if(first_load == 1){
        
        initialize(fp);
        first_load = 0;
        return fp;
    }
}

void readNextBuffer(){
    if(switched)
    {
        switched = 0;
        return;
    }
    else
    {
        if(b_id == 1)
        {
            int read = fread(b.one,sizeof(char),BufferSize,fp);
            if(read != sizeof(char) * BufferSize) b.one[read] = NULL;
        }
        else
        {
            int read = fread(b.two,sizeof(char),BufferSize,fp);
            if(read != sizeof(char) * BufferSize) b.two[read] = NULL;
        }
    }
    
}


void flipBuffer(){ // USED BY FORWARD TO SWITCH BUFFER
    readNextBuffer();
    b_id = (b_id+1)%2;
}

void retract(int n, int* indexptr){
    if(forward-n>=0) {
        forward -= n;
    }
    else{
        b_id = (b_id+1)%2;
        switched = 1;
        forward = forward - n + BufferSize;
    }
    int index = *indexptr - 1;
    while(n-->0) lexeme[index--] = '\0';
    *indexptr = index+1;
}

char getNextChar(int num){
    if(b_id == 0) lexeme[num] = b.one[forward++];
    else lexeme[num] = b.two[forward++];

    if(forward>=BufferSize)
    {
        flipBuffer();
        forward = 0;
    } 
    
    return lexeme[num];
}

void resetLexeme(int* indexptr){
    *indexptr = 0;
    for(int i = 0; i<MAX_LEXEME; i++)
    {
        if(lexeme[i] == NULL) break;
        else lexeme[i] = '\0';
    }
}

tokenInfo* getNextToken(){
    char c; // Stores character pointed by forward pointer in either buffer one or buffer two
    int index = 0;
    int state = 1;
    lexeme = (char*) malloc(MAX_LEXEME);
    t = (tokenInfo*) malloc(sizeof(tokenInfo));
    while(state > -1){
        switch(state){
            
            case 1:  // start state
            {   
                c = getNextChar(index++);
                if(c == '\n') state = 48;
                else if (c == ':')  state = 12;
                else if (c == '<')  state = 17;
                else if (c == '*')  state = 15;
                else if (c == '+')  state = 20;
                else if (c == '>')  state = 25;
                else if (c == '(')  state = 33;
                else if (c == '-')  state = 34;
                else if (c == '/')  state = 37;
                else if (c == ',')  state = 38;
                else if (c == ';')  state = 39;
                else if (c == '!')  state = 40;
                else if (c == '[')  state = 45;
                else if (c == ']')  state = 42;
                else if (c == '=')  state = 43;
                else if (c == '\t' || c == ' ' || c == '\r') state = 46;
                else if (c == ')')  state = 47;
                else if (c == '.')  state = 49;
                else if (c == NULL) state = 51;
                else if (c >= '0' && c <= '9')  state = 2;
                else if ((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || c == '_')  state = 35;
                else { 
                    state = 1;
                    printf("\033[0;31mError: Invalid character : Line Number %d \033[0m  \n", line);
                }
                break;
            }

            case 2: 
            {
                c = getNextChar(index++);
                if (c >= '0' && c <= '9') state = 2; // self loop
                else if (c == '.') state = 3; // real num
                else {
                    t->token = NUM;
                    t->line_num = line;
                    retract(1, &index);
                    long long temp = strtoll(lexeme, NULL, 10);
                    if(temp == LLONG_MAX)
                    {
                        printf("\033[0;31mError: Integer size too big : Line Number %d \033[0m  \n", line);
                        state = 1;
                        break;
                    } 
                    t->tv.i_val = temp;
                    state = 1;
                    return t; 
                }
                break;
            }

            case 3:
            {
                c = getNextChar(index++);
                if (c >= '0' && c <= '9') state = 4;
                else if(c == '.')
                {   
                    t->token = NUM;
                    t->line_num = line;
                    retract(2, &index);
                    long long temp = strtoll(lexeme, NULL, 10);
                    if(temp == LLONG_MAX)
                    {
                        printf("\033[0;31mError: Integer size too big : Line Number %d \033[0m  \n", line);
                        state = 1;
                        break;
                    }
                    t->tv.i_val = temp;
                    state = 1;
                    return t; 
                }
                else { 
                    state = 1;
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m  \n",line);
                    retract(1, &index);
                    resetLexeme(&index);
                }
                break;
            }

            case 4:
            {
                c = getNextChar(index++);
                if (c >= '0' && c <= '9') state = 4;
                else if(c == 'E' || c == 'e') state = 5;
                else
                {   
                    t->token = RNUM;
                    t->line_num = line;
                    retract(1, &index);
                    t->tv.f_val = atof(lexeme);
                    state = 1;
                    return t; 
                }
                break;
            }

            case 5:
            {
                c = getNextChar(index++);
                if(c == '+' || c == '-'){
                    state = 11;
                }
                else if (c >= '0' && c <= '9') state = 6;
                else if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || c == '_' )
                {
                    t->token = RNUM;
                    t->line_num = line;
                    retract(2, &index);
                    t->tv.f_val = atof(lexeme);
                    state = 1;
                    return t;
                }
                else{ 
                    state = 1; 
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m \n", line);
                    retract(1, &index);
                    resetLexeme(&index);
                }
                break;
            }

            case 11:
            {
                c = getNextChar(index++);
                if (c >= '0' && c <= '9')
                {
                    state = 6;
                }
                else { 
                    state = 1;
                    retract(1, &index);
                    resetLexeme(&index);
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m \n", line);
                }
                break;
            }
            case 6:
            {
                c = getNextChar(index++);
                
                if (c >= '0' && c <= '9') state = 6;
                else
                {   
                    t->token = RNUM;
                    t->line_num = line;
                    retract(1, &index);
                    t->tv.f_val = atof(lexeme);
                    state = 1;
                    return t; 
                }
                break;   
            }

            case 12:
            {
                c = getNextChar(index++);
                if(c == '=') state = 13;
                else{
                    t->token = COLON;
                    t->line_num = line;
                    retract(1, &index);
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t;
                } 
                break;
            }

            case 17:
            {
                c = getNextChar(index++);
                if(c == '<') state = 18;
                else if(c == '=')
                {
                    t->token = LE;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t;
                }
                else{
                    t->token = LT;
                    t->line_num = line;
                    retract(1, &index);
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                } 
                break;
            }

            case 18:
            {
                c = getNextChar(index++);
                if(c == '<')
                {
                    t->token = DRIVERDEF;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else{
                    t->token = DEF;
                    t->line_num = line;
                    retract(1, &index);
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                } 
                break;
            }

            case 25:
            {
                c = getNextChar(index++);
                if(c == '>') state = 26;
                else if(c == '=')
                {
                    t->token = GE;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else{
                    t->token = GT;
                    t->line_num = line;
                    retract(1, &index);
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                } 
                break;
            }

            case 26:
            {
                c = getNextChar(index++);
                if(c == '>')
                {
                    t->token = DRIVERENDDEF;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t;
                }
                else
                {
                    t->token = ENDDEF;
                    t->line_num = line;
                    retract(1, &index);
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t;
                }
                break;
            }

            case 35:
            {
                c = getNextChar(index++);
                if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || c == '_' || (c>='0' && c<='9')){
                    charCount++;
                    state = 35;
                }
                else state = 36;
                break;
            }

            case 15:
            {
                c = getNextChar(index++);
                if(c == '*') state = 21;
                else 
                {
                    t->token = MUL;
                    t->line_num = line;
                    retract(1, &index);
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                break;
            }

            case 21:
            {
                c = getNextChar(index++);
                if(c == '*') state = 28;
                else if(c == NULL)
                {
                    printf("\033[0;31mError: Reached EOF : Line Number %d \033[0m  \n",line);
                    t->line_num = line;
                    t->token = ENDOFFILE;
                    state = -1;
                    return t;
                }
                else if(c == '\n')
                {
                    line++;
                    state = 21;
                }
                else state = 21;
                break;
            }

            case 28:
            {
                c = getNextChar(index++);
                if(c == '*') state = 29;
                else state = 21;
                break;
            }

            case 40:
            {
                c = getNextChar(index++);
                if(c == '=')
                {
                    t->token = NE;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else if(c == NULL)
                {
                    printf("\033[0;31mError: Reached EOF: Line Number %d \033[0m  \n",line);
                    t->line_num = line;
                    t->token = ENDOFFILE;
                    state = -1;
                    return t;
                }
                else { 
                    state = 1;
                    retract(1, &index);
                    resetLexeme(&index);
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m  \n",line);
                }
                break;
            }

            case 43:
            {
                c = getNextChar(index++);
                if(c == '=')
                {
                    t->token = EQ;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else if(c == NULL)
                {
                    printf("\033[0;31m Error: Reached EOF: Line Number %d \033[0m  \n",line);
                    t->line_num = line;
                    t->token = ENDOFFILE;
                    state = -1;
                    return t;
                }
                else { 
                    state = 1;
                    retract(1, &index);
                    resetLexeme(&index);
                    printf("\033[0;31mError: Invalid character : Line Number %d \033[0m  \n", line);
                }
                break;
            }

            case 49:
            {
                c = getNextChar(index++);
                if(c == '.')
                {
                    t->token = RANGEOP;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else if(c == NULL)
                {
                    printf("\033[0;31m Error: Reached EOF: Line Number %d \033[0m  \n",line);
                    t->line_num = line;
                    t->token = ENDOFFILE;
                    state = -1;
                    return t;
                }
                else { 
                    state = 1;
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m  \n",line);
                    retract(1, &index);
                    resetLexeme(&index);
                }
                break;
            }

            case 9:
            {
                    
                    t->token = NUM;
                    t->line_num = line;
                    retract(2, &index);
                    t->tv.i_val = atoi(lexeme);
                    state = 1;
                    return t; 
            }

            case 10:
            {
                    t->token = RNUM;
                    t->line_num = line;
                    retract(1, &index);
                    t->tv.f_val = atof(lexeme);
                    state = 1;
                    return t; 
            }

            case 7:
            {
                    
                    t->token = RNUM;
                    t->line_num = line;
                    retract(1, &index);
                    t->tv.f_val = atof(lexeme);
                    state = 1;
                    return t; 
            }

            case 13:
            {
                    t->token = ASSIGNOP;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 29:
            {
                resetLexeme(&index);
                state = 1;
                break;
            }

            case 20:
            {
                    t->token = PLUS;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 33:
            {
                    t->token = BO;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 34:
            {
                    t->token = MINUS;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 37:
            {
                    t->token = DIV;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 36:
            {
                    if(charCount>20)
                    {
                        state = 1; 
                        charCount = 1;
                        retract(1, &index);
                        resetLexeme(&index);
                        printf("\033[0;31mError: Len of string too long : Line Number %d \033[0m \n", line);
                        break;
                    }
                    t->line_num = line;
                    retract(1, &index);
                    for(int i = strlen(lexeme)-1; i>=0; i--)
                    {
                        if(isspace(lexeme[i])) lexeme[i] = '\0';
                    }
                    if(getToken(lexeme, ht) == ID) t->token = ID;
                    else
                    {
                        t->token = getToken(lexeme, ht);
                    } 
                    
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    charCount = 1;
                    return t; 
            }

            case 38:
            {
                    t->token = COMMA;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 39:
            {
                    t->token = SEMICOL;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 42:
            {
                    t->token = SQBC;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 45:
            {
                    t->token = SQBO;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 44:
            {
                    t->token = EQ;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 47:
            {
                    t->token = BC;
                    t->line_num = line;
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 48: 
            {
                index--;
                line++;
                state = 1;
                break;
            }

            case 46: 
            {
                index--;
                state = 1;
                break;
            }

            case 51:
            {
                t->line_num = line;
                t->token = ENDOFFILE;
                state = -1;
                return t;
            }
        }
    }
}

// HELPER FUNCTION
void printToken(tokenInfo* currToken)
{
    if(currToken->token == NUM) printf("%lld", currToken->tv.i_val);
    else if(currToken->token ==RNUM) printf("%f", currToken->tv.f_val);    
    else printf("%s", currToken->tv.lexeme);
}

void printT(token token){
    switch(token){
    case 0: printf("INTEGER"); break;
    case 1: printf("REAL"); break;
    case 2: printf("BOOLEAN"); break;
    case 3: printf("OF"); break; 
    case 4: printf("ARRAY"); break;
    case 5: printf("START"); break;
    case 6: printf("END"); break;
    case 7: printf("DECLARE"); break;
    case 8: printf("MODULE"); break;
    case 9: printf("DRIVER"); break;
    case 10: printf("PROGRAM"); break;
    case 11: printf("GET_VALUE"); break;
    case 12: printf("PRINT"); break;
    case 13: printf("USE"); break;
    case 14: printf("WITH"); break;
    case 15: printf("PARAMETERS"); break;
    case 16: printf("TAKES"); break;
    case 17: printf("INPUT"); break;
    case 18: printf("RETURNS"); break;
    case 19: printf("FOR"); break;
    case 20: printf("IN"); break;
    case 21: printf("SWITCH"); break;
    case 22: printf("CASE"); break;
    case 23: printf("BREAK"); break;
    case 24: printf("DEFAULT"); break;
    case 25: printf("WHILE"); break;
    case 26: printf("ID"); break;
    case 27: printf("NUM"); break;
    case 28: printf("RNUM"); break;
    case 29: printf("AND"); break;
    case 30: printf("OR"); break;
    case 31: printf("TRUE"); break;
    case 32: printf("FALSE"); break;
    case 33: printf("PLUS"); break;
    case 34: printf("MINUS"); break;
    case 35: printf("MUL"); break;
    case 36: printf("DIV"); break;
    case 37: printf("LT"); break;
    case 38: printf("LE"); break;
    case 39: printf("GE"); break;
    case 40: printf("GT"); break;
    case 41: printf("EQ"); break;
    case 42: printf("NE"); break;
    case 43: printf("DEF"); break;
    case 44: printf("ENDDEF"); break;
    case 45: printf("DRIVERDEF"); break;
    case 46: printf("DRIVERENDDEF"); break;
    case 47: printf("COLON"); break;
    case 48: printf("RANGEOP"); break;
    case 49: printf("SEMICOL"); break;
    case 50: printf("COMMA"); break;
    case 51: printf("ASSIGNOP"); break;
    case 52: printf("SQBO"); break;
    case 53: printf("SQBC"); break;
    case 54: printf("BO"); break;
    case 55: printf("BC"); break;
    case 56: printf("COMMENTMARK"); break;
    case 57: printf("ENDOFFILE"); break;
    case 58: printf("EPSILON"); break;
    default: printf("<unknown>"); break;
    }
    printf(" ");
}

void fprintT(FILE* fp, token token){
    switch(token){
    case 0: fprintf(fp,"INTEGER"); break;
    case 1: fprintf(fp,"REAL"); break;
    case 2: fprintf(fp,"BOOLEAN"); break;
    case 3: fprintf(fp,"OF"); break; 
    case 4: fprintf(fp,"ARRAY"); break;
    case 5: fprintf(fp,"START"); break;
    case 6: fprintf(fp,"END"); break;
    case 7: fprintf(fp,"DECLARE"); break;
    case 8: fprintf(fp,"MODULE"); break;
    case 9: fprintf(fp,"DRIVER"); break;
    case 10: fprintf(fp,"PROGRAM"); break;
    case 11: fprintf(fp,"GET_VALUE"); break;
    case 12: fprintf(fp,"PRINT"); break;
    case 13: fprintf(fp,"USE"); break;
    case 14: fprintf(fp,"WITH"); break;
    case 15: fprintf(fp,"PARAMETERS"); break;
    case 16: fprintf(fp,"TAKES"); break;
    case 17: fprintf(fp,"INPUT"); break;
    case 18: fprintf(fp,"RETURNS"); break;
    case 19: fprintf(fp,"FOR"); break;
    case 20: fprintf(fp,"IN"); break;
    case 21: fprintf(fp,"SWITCH"); break;
    case 22: fprintf(fp,"CASE"); break;
    case 23: fprintf(fp,"BREAK"); break;
    case 24: fprintf(fp,"DEFAULT"); break;
    case 25: fprintf(fp,"WHILE"); break;
    case 26: fprintf(fp,"ID"); break;
    case 27: fprintf(fp,"NUM"); break;
    case 28: fprintf(fp,"RNUM"); break;
    case 29: fprintf(fp,"AND"); break;
    case 30: fprintf(fp,"OR"); break;
    case 31: fprintf(fp,"TRUE"); break;
    case 32: fprintf(fp,"FALSE"); break;
    case 33: fprintf(fp,"PLUS"); break;
    case 34: fprintf(fp,"MINUS"); break;
    case 35: fprintf(fp,"MUL"); break;
    case 36: fprintf(fp,"DIV"); break;
    case 37: fprintf(fp,"LT"); break;
    case 38: fprintf(fp,"LE"); break;
    case 39: fprintf(fp,"GE"); break;
    case 40: fprintf(fp,"GT"); break;
    case 41: fprintf(fp,"EQ"); break;
    case 42: fprintf(fp,"NE"); break;
    case 43: fprintf(fp,"DEF"); break;
    case 44: fprintf(fp,"ENDDEF"); break;
    case 45: fprintf(fp,"DRIVERDEF"); break;
    case 46: fprintf(fp,"DRIVERENDDEF"); break;
    case 47: fprintf(fp,"COLON"); break;
    case 48: fprintf(fp,"RANGEOP"); break;
    case 49: fprintf(fp,"SEMICOL"); break;
    case 50: fprintf(fp,"COMMA"); break;
    case 51: fprintf(fp,"ASSIGNOP"); break;
    case 52: fprintf(fp,"SQBO"); break;
    case 53: fprintf(fp,"SQBC"); break;
    case 54: fprintf(fp,"BO"); break;
    case 55: fprintf(fp,"BC"); break;
    case 56: fprintf(fp,"COMMENTMARK"); break;
    case 57: fprintf(fp,"ENDOFFILE"); break;
    case 58: fprintf(fp,"EPSILON"); break;
    default: fprintf(fp,"<unknown>"); break;
    }
    printf(" ");
}

void removeComments(char *testcaseFile, char *cleanFile)
{
    char ch;
    FILE* fp1 = fopen(testcaseFile, "r");
    if(fp1 == NULL) printf("Couldn't open file to read\n");
    FILE* fp2 = fopen(cleanFile, "w");
    if(fp2 == NULL) printf("Couldn't open file to write\n");
    int found = 0;
    int new_lines = 0;
    while((ch=fgetc(fp1))!=EOF)
    {
        if(ch == '*')
        {
            char ch2 = fgetc(fp1);
            if(ch2 != EOF)
            {
                if(ch2 == '*')
                {
                    if(!found) found = 1;
                    else
                    {
                        while(new_lines-->0)
                        {
                            fputc('\n', fp2);
                            printf("\n");
                        } 
                        found = 0;
                        new_lines = 0;
                    } 
                    continue;
                } 
                else
                {
                    fputc('*', fp2);
                    fputc(ch2, fp2);
                    printf("*");
                    printf("%c", ch2);
                    continue;
                }
            }
            else
            {
                fputc('*', fp2);
                printf("*");
                break;
            }
        }
        if(found)
        {
            if(ch == '\n') new_lines++;
            fputc(' ', fp2);
            printf(" ");
        } 
        else
        {
            fputc(ch, fp2);
            printf("%c", ch);
        } 
    }
    fclose(fp1);
    fclose(fp2);
}

tokenInfo * runLexerForParser(char* testfile, int size)
{
    if(fp == NULL){
        fp = fopen(testfile,"r");
        BufferSize = size;
        fp = getStream(fp);
    }
    tokenInfo * parserToken = (tokenInfo *) malloc( sizeof(tokenInfo));
    parserToken = getNextToken();
    // if(parserToken->token == ENDOFFILE)
    // {
    //     freeData();
    // }
    // INSERT THIS INSIDE YOUR PARSER
    return parserToken;
}

void runLexer(char* testfile, int size)
{
    fp = fopen(testfile,"r");
    BufferSize = size;
    fp = getStream(fp);
    tokenInfo * tk = (tokenInfo *) malloc( sizeof(tokenInfo));
    tk = getNextToken();
    while(tk->token != ENDOFFILE)
    {
        printf("\nLine no\tLexeme\ttoken_name\n");
        printf("%d\t",tk->line_num);
        printToken(tk);
        printf("\t");
        printT(tk->token);
        printf("\n");
        tk = getNextToken();
    } 
    freeData();
    free(tk);
}

void freeData()
{
    free(lexeme);
    free(b.one);
    free(b.two);
    charCount = 1;
    first_load = 1;
    spill = 0;
    switched = 0;
    if(fclose(fp) == 0) fp = NULL;
    else printf("File not closed successfully\n");
}

#endif