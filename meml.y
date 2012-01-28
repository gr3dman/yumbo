%{
#include <stdio.h>
#include <strings.h>

#include "meml.h"

#define SIZE_STATES 128

static t_state states[SIZE_STATES];
static int head = 0;
static t_state *current;

static void term();
static void table(char *name);

static void inherit();

static void cardinal1(enum cardinal card);
static void cardinal2(enum cardinal card);

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

			cardinal2($6);
		 }
		 | '^' '-' Dotted { inherit(); }
		 ;

Cardinal : '1'	{ $$ = CARD_ONE; }
		 | '*'	{ $$ = CARD_MANY; }
		 | '0' '.' '.' '*'	{ $$ = CARD_ZERO_MANY; }
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

void term() {
	current = &states[++head];
}

void table(char *name) {
	char *buff;
	int len = strlen(name);
	if (!current->table1)
		buff = current->table1 = malloc(len * sizeof (char));
	else
		buff = current->table2 = malloc(len * sizeof (char));
	strncpy(buff, name, len);
}

void inherit() {
	current->inherit = 1;
}

void cardinal1(enum cardinal card) {
	current->cardinal1 = card;
}

void cardinal2(enum cardinal card) {
	current->cardinal2 = card;
}

void print_cardinality(char *fmt, enum cardinal card) {
	printf(fmt, card == CARD_ONE ? "one"
				: card == CARD_MANY ? "many"
				: card == CARD_ZERO_MANY ? "zero or many"
				: "unknown");
}

void print_state(t_state *state) {
	printf("table1 %s\n", state->table1);
	if (state->inherit)
		printf("inherit\n");
	if (state->cardinal1)
		print_cardinality("left cardinality: %s", state->cardinal1);
	if (state->cardinal2)
		print_cardinality("right cardinality: %s", state->cardinal2);
}

void print_states() {
	int i;
	for (i = 0; i < head; i++) {
		print_state(&states[i]);
	}
}

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

int main() {
	int result = 0;

	bzero(states, sizeof (t_state) * SIZE_STATES);
	current = &states[0];

	result = yyparse();
	if (!result)
		print_states();

	return result;
}
