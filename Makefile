meml:	lex.yy.c y.tab.c
		cc -o meml *.c

lex.yy.c:	meml.l y.tab.c
			flex meml.l

y.tab.c:	meml.y
			yacc -vdt meml.y

clean:
		rm lex.yy.* y.tab.* y.output
