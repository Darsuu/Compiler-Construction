
# Group No. : 42
# ID: 2020A7PS1214P	Name: Darshan Abhaykumar
# ID: 2020A7PS0970P	Name: Debjit Kar
# ID:2020A7PS0986P	Name: Nidhish Parekh

runCompiler: driver.o grammar.o lexer.o linkedlist.o parser.o tree.o stack_ll.o HTable.o Nlinkedlist.o
	gcc -o runCompiler driver.o grammar.o lexer.o linkedlist.o parser.o tree.o stack_ll.o HTable.o Nlinkedlist.o
driver.o: driver.c
	gcc -c driver.c
grammar.o: grammar.c grammarDef.h
	gcc -c grammar.c
linkedlist.o: linkedlist.c lexerDef.h
	gcc -c linkedlist.c 
lexer.o: lexer.c lexerDef.h
	gcc -c lexer.c
parser.o: parser.c parserDef.h 
	gcc -c parser.c 
tree.o: tree.c treeDef.h
	gcc -c tree.c
stack_ll.o: stack_ll.c stackDef.h
	gcc -c stack_ll.c
HTable.o: HTable.c
	gcc -c HTable.c
Nlinkedlist.o: Nlinkedlist.c
	gcc -c Nlinkedlist.c
clean: 
	rm *.o runCompiler