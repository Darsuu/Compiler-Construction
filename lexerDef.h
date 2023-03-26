/*
Group No.: 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/

/* Definitions of data structures for lexer*/
#ifndef LEXERDEF_H
#define LEXERDEF_H
#define MAX_LEXEME (1<<15)
#define TOKEN_COUNT 60
typedef enum { 
    INTEGER,
     REAL,
     BOOLEAN,
     OF,
     ARRAY,
     START,
     END,
     DECLARE,
    MODULE,
     DRIVER,
     PROGRAM,
     GET_VALUE,
     PRINT,
    USE,
     WITH,
     PARAMETERS,
     TAKES,
     INPUT,
    RETURNS,
     FOR,
     IN,
     SWITCH,
     CASE,
    BREAK,
     DEFAULT,
     WHILE,
     ID,
     NUM,
    RNUM,
     AND,
     OR,
     TRUE,
     FALSE,
    PLUS,
     MINUS,
     MUL,
     DIV,
     LT,
    LE,
     GE,
     GT,
     EQ,
     NE,
    DEF,
     ENDDEF,
     DRIVERDEF,
     DRIVERENDDEF,
     COLON,
    RANGEOP,
     SEMICOL,
     COMMA,
     ASSIGNOP,
     SQBO,
    SQBC,
     BO,
     BC,
     COMMENTMARK,
     ENDOFFILE,
     EPSILON
} token;

typedef struct {
    token token;
    int line_num;
    union typeVal{
        long long i_val;
        float f_val;
        char lexeme[MAX_LEXEME];
    } tv;
} tokenInfo;

typedef struct{
    char* one;
    char* two;
} buffer;

typedef struct {
    token sym;
    int valid;
    char lexeme[MAX_LEXEME];
} HTableEntry;

typedef HTableEntry* Htable;
#endif