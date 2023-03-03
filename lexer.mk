runLexer: lexer.o test.o HTable.o
	gcc -o runLexer lexer.o test.o HTable.o
	./runLexer
lexer.o: lexer.c lexerDef.h
	gcc -c lexer.c 
HTable.o: HTable.c hashtable.h
	gcc -c HTable.c
test.o: test.c lexerDef.h lexer.h
	gcc -c test.c
clean: rm -rf *o