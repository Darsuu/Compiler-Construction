/*
Group No. : 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/

/*
	This is the menu driven file. To begin executing the code 
	1> Type 'make'
	2> Type './runCompiler <input_file> <parseTreeOutput> size_of_buffer'
*/

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "grammar.h"
#include "parser.h"
#include "tree.h"
#include "stack.h"
#include "linkedlist.h"
#include "Nlinkedlist.h"
#include "hashtable.h"
#include <time.h>

int main(int argc, char*argv[]){
 
	printf("---------- CAPABILITY OF THE COMPILER ---------- \n\n");
	printf(" --> Twin Buffer implemented\n");
	printf(" --> Implemented lexer module completely\n");
	printf(" --> Union struct used to save on memory\n");
	printf(" --> Parse Table implemented (Can be printed in grammar.c\n");
	printf(" --> Can construct and print N-ary tree\n");
	printf("-------------------------------------------------- \n\n");

	printf("---------- SHORTCOMINGS OF THE COMPILER ---------- \n\n");
	printf(" --> Parser doesn't work \n");
	printf(" --> Parse tree not complete (N-ary tree created) \n");
	printf(" --> First and Follow not automated\n");
	printf("-------------------------------------------------- \n\n");
	
	int option = 1;
	initializeLexerOnce();
	while(option > 0){
		printf("\n\n\n");
		printf("Press 0 to exit.\n");
		printf("Press 1 to print comment-free code.\n");
		printf("Press 2 to invoke lexer only.\n");
		printf("Press 3 to invoke parser.\n");
		printf("Press 4 to get time taken by parser and lexer.\n");
		printf("\n");
		scanf("%d", &option);
		switch(option){
			case 0:{
				return 0;
			}
			case 1:{
				removeComments(argv[1],"cleanFile.txt");
				break; 
			}
			case 2:{
				runLexer(argv[1], atoi(argv[3]));
				break;
			}
			case 3:{
				runGrammar();
				// runParser();
				// // CREATING A SAMPLE PARSE TREE HERE TO DEMONSTRATE THE PRINTING AND FORMING OF PARSE TREE
				// // THIS IS NOT THE PARSE TREE THAT IS GENERATED FROM THE INPUT FILE
				// runTree(argv[2]);
				break;
			}
			case 4:{
				clock_t start_time, end_time;
				double total_CPU_time, total_CPU_time_in_seconds;

				start_time = clock();
				runLexer(argv[1], atoi(argv[3]));
				runParser();
				end_time = clock();

				total_CPU_time = (double) (end_time - start_time);
				total_CPU_time_in_seconds = total_CPU_time /CLOCKS_PER_SEC;

				printf("total_CPU_time = %f \n",total_CPU_time);
				printf("total_CPU_time_in_seconds = %f seconds \n",total_CPU_time_in_seconds);
				break;
			}
		}
	}
}