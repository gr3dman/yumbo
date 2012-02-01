memldot:	dot.c parse.c lex.yy.c y.tab.c
			cc -o memldot dot.c parse.c lex.yy.c y.tab.c

testrunner:	test.c parse.c lex.yy.c y.tab.c
			cc -o testrunner test.c parse.c lex.yy.c y.tab.c

lex.yy.c:	meml.l y.tab.c
			lex meml.l

y.tab.c:	meml.y
			yacc -vdt meml.y

test:	testrunner
		cd tests && ./run.sh

clean:
		rm -f lex.yy.* y.tab.* y.output
