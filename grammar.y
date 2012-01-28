%{
#include "meml.h"

%}

%token T_Word

%%

Diagram : Term				{ term(); }
		| Term ',' Diagram
		;

Term : Pair
	 | Table
	 ;

Pair : Table Relation Table
	 ;

Table : '[' T_Word ']' { table(word); }
	  ;

Relation : Cardinal Attr '-' Dotted Arrow Cardinal {
			cardinal1($1);
			attribute($2);
			cardinal2($6);
		 }
		 | '^' '-' Dotted { inherit(); }
		 ;

Cardinal : '1'	{ $$ = CARD_ONE; }
		 | '*'	{ $$ = CARD_MANY; }
		 | '0' '.' '.' '*'	{ $$ = CARD_ZERO_MANY; }
		 |
		 ;

Attr : '<' '>'	{ $$ = ATTR_AGGREGATE; }
	 | '+' '+'	{ $$ = ATTR_COMPOSE; }
	 | '<'		{ $$ = ATTR_REVERSE_ARROW; }
	 | 
	 ;

Dotted : '.' '-'	{ dotted(); }
		 |
		 ;

Arrow : '>'		{ arrow(); }
		|
		;

%%
