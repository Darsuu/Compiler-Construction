#ifndef LEXER_C
#define LEXER_C
#include "lexerDef.h"
#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int line, b_id, forward, begin, i;
int charCount = 1;
int first_load = 1;
int spill = 0;
buffer b;
HTableEntry ht[MODULO];

int b_idB,b_idF;
char *lexeme;

void initialize(FILE *fp){
    memset(b.one,0,sizeof(b.one));
    memset(b.two,0,sizeof(b.two));
    b_id = 1;
    b_idF = 1;
    line = 1;
    forward = 0;
    begin = 0;
    for(i=0;i<MODULO;i++) ht[i].valid = 0;
    initTable(ht);
    fread(b.one,sizeof(char),BUFFER_SIZE,fp); // CHANGED
    fread(b.two,sizeof(char),BUFFER_SIZE,fp); // CHANGED
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

    if(b_id == 2){
        fread(b.one,BUFFER_SIZE,1,fp);
        b_id = 1;
        return fp;
    }

    else{
        fread(b.two,BUFFER_SIZE,1,fp);
        b_id = 2;
        return fp;
    }
}
void flipBuffer(char c){
    if(c == 'B'){
        if(b_idB == 1) b_idB = 2;
        else b_idB = 1;
    }
    if(c == 'F'){
        if(b_idF == 1) b_idF = 2;
        else b_idF = 1;
    }
}
void retract(int n){
    if(forward-n>=0) {
        forward -= n;
    }
    else{
        flipBuffer('F');
        forward = forward - n + BUFFER_SIZE;
    }
    if(begin-n>=0) {
        begin -= n;
    }
    else{
        flipBuffer('B');
        begin = begin - n + BUFFER_SIZE;
    }

    if(begin!=forward) printf("\n**Error in retraction**\n");
}

char getNextChar(){
    if(forward+1>BUFFER_SIZE){
        flipBuffer('F');
        forward -= BUFFER_SIZE;
    }
    if(b_idF==1) return b.one[forward++];
    else return b.two[forward++];
}

void incB(){
    if(++begin>BUFFER_SIZE){
        flipBuffer('B');
        begin -= BUFFER_SIZE;
    }
}

tokenInfo* getNextToken(){
    char c; // Stores character pointed by forward pointer in either buffer one or buffer two
    int state = 1;
    lexeme = (char*) malloc(MAX_LEXEME);
    tokenInfo* t = (tokenInfo*) malloc(sizeof(tokenInfo));

    while(state > -1){
        switch(state){
           
            case 1:  // start state
            {   
                c = getNextChar();
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
                else if (c == '\t' || c == ' ') state = 46;
                else if (c == ')')  state = 47;
                else if (c == '.')  state = 49;
                else if (c == NULL) state = 51;
                else if (c >= '0' && c <= '9')  state = 2;
                else if ((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || c == '_')  state = 35;
                else { 
                    state = 1;
                    incB();
                    printf("\033[0;31mError: Invalid character : Line Number %d \033[0m  \n", line);
                }
                break;
            }

            case 2: 
            {
                c = getNextChar();
                if (c >= '0' && c <= '9') state = 2; // self loop
                else if (c == '.') state = 3; // real num
                else {
                    t->token = NUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    long long temp = strtoll(lexeme, NULL, 10);
                    if(temp == LLONG_MAX)
                    {
                        printf("\033[0;31mError: Integer size too big : Line Number %d \033[0m  \n", line);
                        state = 1;
                        break;
                    } 
                    t->tv.i_val = temp;
                    incB();
                    retract(1);
                    state = 1;
                    return t; 
                }
                break;
            }

            case 3:
            {
                c = getNextChar();
                if (c >= '0' && c <= '9') state = 4;
                else if(c == '.')
                {   
                    t->token = NUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    long long temp = strtoll(lexeme, NULL, 10);
                    if(temp == LLONG_MAX)
                    {
                        printf("\033[0;31mError: Integer size too big : Line Number %d \033[0m  \n", line);
                        state = 1;
                        break;
                    }
                    t->tv.i_val = temp;
                    retract(2);
                    state = 1;
                    return t; 
                }
                else { 
                    state = 1;
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m  \n",line);
                    begin = forward;
                    retract(1);
                }
                break;
            }

            case 4:
            {
                c = getNextChar();
                if (c >= '0' && c <= '9') state = 4;
                else if(c == 'E' || c == 'e') state = 5;
                else
                {   
                    t->token = RNUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    t->tv.f_val = atof(lexeme);
                    retract(1);
                    state = 1;
                    return t; 
                }
                break;
            }

            case 5:
            {
                c = getNextChar();
                if(c == '+' || c == '-'){
                    state = 11;
                }
                else if (c >= '0' && c <= '9') state = 6;
                else if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || c == '_' )
                {
                    t->token = RNUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward-2;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    incB();
                    t->tv.f_val = atof(lexeme);
                    retract(2);
                    state = 1;
                    return t;
                }
                else{ 
                    state = 1; 
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m \n", line);
                    begin = forward;
                    retract(1);
                }
                break;
            }

            case 11:
            {
                c = getNextChar();
                if (c >= '0' && c <= '9')
                {
                    state = 6;
                }
                else { 
                    state = 1;
                    begin = forward;
                    retract(1);
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m \n", line);
                }
                break;
            }
            case 6:
            {
                c = getNextChar();
                
                if (c >= '0' && c <= '9') state = 6;
                else
                {   
                    t->token = RNUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    t->tv.f_val = atof(lexeme);
                    retract(1);
                    state = 1;
                    return t; 
                }
                break;   
            }

            case 12:
            {
                c = getNextChar();
                if(c == '=') state = 13;
                else{
                    t->token = COLON;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    return t;
                } 
                break;
            }

            case 17:
            {
                c = getNextChar();
                if(c == '<') state = 18;
                else if(c == '=')
                {
                    t->token = LE;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t;
                }
                else{
                    t->token = LT;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    return t; 
                } 
                break;
            }

            case 18:
            {
                c = getNextChar();
                if(c == '<')
                {
                    t->token = DRIVERDEF;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else{
                    t->token = DEF;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    return t; 
                } 
                break;
            }

            case 25:
            {
                c = getNextChar();
                if(c == '>') state = 26;
                else if(c == '=')
                {
                    t->token = GE;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else{
                    t->token = GT;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    return t; 
                } 
                break;
            }

            case 26:
            {
                c = getNextChar();
                if(c == '>')
                {
                    t->token = DRIVERENDDEF;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t;
                }
                else
                {
                    t->token = ENDDEF;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    return t;
                }
                break;
            }

            case 35:
            {
                c = getNextChar();
                if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || c == '_' || (c>='0' && c<='9')){
                    charCount++;
                    state = 35;
                }
                else state = 36;
                break;
            }

            case 15:
            {
                c = getNextChar();
                if(c == '*') state = 21;
                else 
                {
                    t->token = MUL;
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    return t; 
                }
                break;
            }

            case 21:
            {
                c = getNextChar();
                if(c == '*') state = 28;
                else if(c == NULL)
                {
                    printf("\033[0;31mError: Reached EOF : Line Number %d \033[0m  \n",line);
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
                c = getNextChar();
                if(c == '*') state = 29;
                else state = 21;
                break;
            }

            case 40:
            {
                c = getNextChar();
                if(c == '=')
                {
                    t->token = NE;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else if(c == NULL)
                {
                    printf("\033[0;31mError: Reached EOF: Line Number %d \033[0m  \n",line);
                    state = -1;
                    return t;
                }
                else { 
                    state = 1;
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m  \n",line);
                    incB();
                    incB();
                    retract(1);
                }
                break;
            }

            case 43:
            {
                c = getNextChar();
                if(c == '=')
                {
                    t->token = EQ;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else if(c == NULL)
                {
                    printf("\033[0;31m Error: Reached EOF: Line Number %d \033[0m  \n",line);
                    state = -1;
                    return t;
                }
                else { 
                    state = 1;
                    incB();
                    incB();
                    retract(1);
                    printf("\033[0;31mError: Invalid character : Line Number %d \033[0m  \n", line);
                }
                break;
            }

            case 49:
            {
                c = getNextChar();
                if(c == '.')
                {
                    t->token = RANGEOP;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
                }
                else if(c == NULL)
                {
                    printf("\033[0;31m Error: Reached EOF: Line Number %d \033[0m  \n",line);
                    state = -1;
                    return t;
                }
                else { 
                    state = 1;
                    printf("\033[0;31mError: Invalid pattern : Line Number %d \033[0m  \n",line);
                    incB();
                    incB();
                    retract(1);
                }
                break;
            }

            case 9:
            {
                    
                    t->token = NUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    t->tv.i_val = atoi(lexeme);
                    retract(2);
                    state = 1;
                    return t; 
            }

            case 10:
            {
                    t->token = RNUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    t->tv.f_val = atof(lexeme);
                    retract(1);
                    state = 1;
                    return t; 
            }

            case 7:
            {
                    
                    t->token = RNUM;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    t->tv.f_val = atof(lexeme);
                    retract(1);
                    state = 1;
                    return t; 
            }

            case 13:
            {
                    t->token = ASSIGNOP;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 29:
            {
                begin = forward;
                state = 1;
                break;
            }

            case 20:
            {
                    t->token = PLUS;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 33:
            {
                    t->token = BO;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 34:
            {
                    t->token = MINUS;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 37:
            {
                    t->token = DIV;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
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
                        begin = forward;
                        retract(1);
                        printf("\033[0;31mError: Len of string too long : Line Number %d \033[0m \n", line);
                        break;
                    }
                    t->line_num = line;
                    for(int i = 0;begin<forward-1;incB(),i++){
                        lexeme[i] = b.one[begin];
                    } 
                    if(getToken(lexeme, ht) == ID) t->token = ID;
                    else t->token = getToken(lexeme, ht);
                    incB();
                    strcpy(t->tv.lexeme, lexeme);
                    retract(1);
                    state = 1;
                    charCount = 1;
                    return t; 
            }

            case 38:
            {
                    t->token = COMMA;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 39:
            {
                    t->token = SEMICOL;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 42:
            {
                    t->token = SQBC;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 45:
            {
                    t->token = SQBO;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }
            case 44:
            {
                    t->token = EQ;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 47:
            {
                    t->token = BC;
                    t->line_num = line;
                    for(int i = 0;begin<forward;incB(),i++){
                        lexeme[i] = b.one[begin];
                    }
                    strcpy(t->tv.lexeme, lexeme);
                    state = 1;
                    return t; 
            }

            case 48: 
            {
                line++;
                incB();
                state = 1;
                break;
            }

            case 46: 
            {
                incB();
                state = 1;
                break;
            }

            case 51:
            {
                t->line_num = line;
                t->token = ENDOFFILE;
                state = -1;
                //printf("File ended\n");
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
                        while(new_lines-->0) fputc('\n', fp2);
                        found = 0;
                        new_lines = 0;
                    } 
                    continue;
                } 
                else
                {
                    fputc('*', fp2);
                    fputc(ch2, fp2);
                    continue;
                }
            }
            else
            {
                fputc('*', fp2);
                break;
            }
        }
        if(found)
        {
            if(ch == '\n') new_lines++;
            fputc(' ', fp2);
        } 
        else fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);
}

void runLexer(void)
{
    FILE * fp = fopen("input.txt","r");
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
}
#endif