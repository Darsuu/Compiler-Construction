runParser: grammar.o lexer.o linkedlist.o parser.o testParser.o tree.o stack_ll.o HTable.o
	gcc -o runParser grammar.o lexer.o linkedlist.o parser.o testParser.o tree.o stack_ll.o HTable.o
	./runParser
grammar.o: grammar.c grammarDef.h
	gcc -c grammar.c
linkedlist.o: linkedlist.c linkedlist.h lexerDef.h grammar.h lexer.h
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
clean: rm -rf *o