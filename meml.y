%{
#include <stdio.h>
#include <assert.h>

#include "meml.h"

%}

%token T_Word

%%

Diagram : Term
		| Term ',' Diagram
		;

Term : Pair
	 | Table
	 ;

Pair : Table Relation Table
	 ;

Table : '[' T_Word ']' { printf("table %s\n", word); }
	  ;

Relation : Cardinal Attr '-' Dotted Arrow Cardinal
		 ;

Cardinal : '1'	{ printf("one\n"); }
		 | '*'	{ printf("many\n"); }
		 | '0' '.' '.' '*'	{ printf("zero or many\n"); }
		 |
		 ;

Attr : '<' '>'	{ printf("aggregate\n"); }
	 | '+' '+'	{ printf("composite\n"); }
	 | '<'		{ printf("reverse arrow\n"); }
	 | 
	 ;

Dotted : '.' '-'	{ printf("dotted\n"); }
		 |
		 ;

Arrow : '>'		{ printf("arrow\n"); }
		|
		;

%%

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

int main() {
	return yyparse();
}
