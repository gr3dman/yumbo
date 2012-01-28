meml:	meml.c lex.yy.c y.tab.c
		cc -o meml *.c

lex.yy.c:	meml.l y.tab.c
			flex meml.l

y.tab.c:	grammar.y
			yacc -vdt grammar.y

test:	meml
		cd tests && ./run.sh

clean:
		rm lex.yy.* y.tab.* y.output
