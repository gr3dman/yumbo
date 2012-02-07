yumbodot:	dot.c parse.c lex.yy.c y.tab.c
			cc -o yumbodot dot.c parse.c lex.yy.c y.tab.c

testrunner:	test.c parse.c lex.yy.c y.tab.c
			cc -o testrunner test.c parse.c lex.yy.c y.tab.c

lex.yy.c:	yuml.l y.tab.c
			lex yuml.l

y.tab.c:	yuml.y
			yacc -vdt yuml.y

test:	testrunner
		cd tests && ./run.sh

clean:
		rm -f lex.yy.* y.tab.* y.output
