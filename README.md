# Compiler Construction Project
Created a compiler for a custom language in C

## Steps to Execute 

1. To compile all the files, run the `make` command.
2. To run the compiler on a file 'input.txt' and storing the Parse Tree as an output in a file called 'output.txt' with a buffer size of 50, run `./runCompiler input.txt output.txt 50`

## Features Implemented
- Twin Buffer
- Lexer
  1. Lexical Error Handling
  2. Keyword Handling
  3. Tokenization
- Parser
  1. Automatic First & Follow of the Grammar
  2. Parser Error Handling
- Parse Tree Generation
- Abstract Syntax Tree Generation
- Symbol Table
- Type Checking
- Semantic Analyzer (Incomplete)

## Approximate DFA for the language
![Compiler](https://github.com/Darsuu/Compiler/assets/81075125/52e4a54d-cdcb-4999-b517-147658d160df)


## Structure of the files
All header files with the 'Def' suffix are being used to implement the structure, while rest
of the header files contain function declarations. 

## Group Members & Contributors
1. Darshan Abhaykumar 2020A7PS1214P
2. Debjit Kar  2020A7PS0970P
3. Nidhish Parekh 2020A7PS0986P
