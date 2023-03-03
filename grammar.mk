runGrammar: grammar.o testGrammar.o linkedlist.o lexer.o 
	gcc -o runGrammar grammar.o testGrammar.o linkedlist.o lexer.o
	./runGrammar
grammar.o: grammar.c grammarDef.h
	gcc -c grammar.c
linkedlist.o: linkedlist.c linkedlist.h lexerDef.h grammar.h lexer.h
	gcc -c linkedlist.c 
testGrammar.o: testGrammar.c grammarDef.h grammar.h linkedlist.h
	gcc -c testGrammar.c
lexer.o: lexer.c lexerDef.h
	gcc -c lexer.c
clean: rm -rf *o