meml:	main.c lex.yy.c y.tab.c
		cc -o meml *.c

lex.yy.c:	meml.l y.tab.c
			lex meml.l

y.tab.c:	meml.y
			yacc -vdt meml.y

test:	meml
		cd tests && ./run.sh

clean:
		rm -f lex.yy.* y.tab.* y.output
