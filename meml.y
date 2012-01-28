%{
#include <stdio.h>
#include <assert.h>

#include "meml.h"

%}

%token T_Word T_Aggregate T_Composite

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

Relation : T_Attr '-' T_Arrow
		 ;

T_Attr : T_Aggregate	{ printf("aggregate\n"); }
	   | T_Composite	{ printf("composite\n"); }
	   |
	   ;

T_Arrow : '>'		{ printf("arrow\n"); }
		|
		;

%%

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

int main() {
	return yyparse();
}
