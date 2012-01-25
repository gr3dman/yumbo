%{
#include <stdio.h>
#include <assert.h>

#include "meml.h"

%}

%token T_Word T_Number T_Arrow T_Line

%%

Diagram : Term
		| Term ',' Diagram
		;

Term : Pair
	 | Table
	 ;

Pair : Table Relation Table { printf("pair\n"); }
	 ;

Table : '[' T_Word ']' { printf("table %s\n", word); }
	  ;

Relation : T_Arrow
		 | T_Line
		 ;

%%

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

int main() {
	return yyparse();
}
