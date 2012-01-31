#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "meml.h"

extern char *yytext;

static t_state states[SIZE_STATES];
static int head = 0;
static t_state *current;
static t_proplist **current_proplist;


void trim(char *str) {
	char *in = str, *out = str, *last;

	while (*in == ' ')
		in++;

	while (*in) {
		if (*in != ' ')
			last = out;
		*(out++) = *(in++);
	}

	*(last+1) = 0;
}


/* parser actions */

void term() {
	current = &states[++head];
	current_proplist = &current->table1;
}

void table() {
	current_proplist = &current->table2;
}

void property(char *prop) {
	int len = strlen(prop) + 1;

	*current_proplist = malloc(sizeof (t_proplist));
	bzero(*current_proplist, sizeof (t_proplist));
	(*current_proplist)->val = malloc(len * sizeof (char));
	strncpy((*current_proplist)->val, prop, len);
	trim((*current_proplist)->val);

	current_proplist = &(*current_proplist)->next;
}

void line() {
	*current_proplist = malloc(sizeof (t_proplist));
	bzero(*current_proplist, sizeof(t_proplist));
	(*current_proplist)->line = 1;

	current_proplist = &(*current_proplist)->next;
}

void attribute(enum attribute attr) {
	current->attribute = attr;
}

void inherit() {
	current->inherit = 1;
}

void arrow() {
	current->arrow = 1;
}

void dotted() {
	current->dotted = 1;
}

void cardinal1(enum cardinal card) {
	current->cardinal1 = card;
}

void cardinal2(enum cardinal card) {
	current->cardinal2 = card;
}


/* print functions */

void print_attribute(enum attribute attr) {
	printf("%s\n", attr == ATTR_REVERSE_ARROW ? "reverse arrow"
			: attr == ATTR_AGGREGATE ? "aggregate"
			: attr == ATTR_COMPOSE ? "composite"
			: "unknown");
}

void print_cardinality(char *fmt, enum cardinal card) {
	printf(fmt, card == CARD_ONE ? "one"
				: card == CARD_MANY ? "many"
				: card == CARD_ZERO_ONE ? "zero or one"
				: card == CARD_ZERO_MANY ? "zero or many"
				: "unknown");
}

void print_proplist(t_proplist *proplist) {
	t_proplist *pl;
	int props;
	for (pl = proplist, props = 0; pl; pl = pl->next, props++)
		if (pl->line)
			printf("line\n");
		else
			printf("%s %s\n", props ? "property" : "table", pl->val);
}

void print_state(t_state *state) {
	/* printf("table %s\n", state->table1); */
	print_proplist(state->table1);
	if (state->inherit)
		printf("inherit\n");
	if (state->cardinal1)
		print_cardinality("%s\n", state->cardinal1);
	if (state->attribute)
		print_attribute(state->attribute);
	if (state->dotted)
		printf("dotted\n");
	if (state->arrow)
		printf("arrow\n");
	if (state->cardinal2)
		print_cardinality("%s\n", state->cardinal2);
	if (state->table2)
		print_proplist(state->table2);
		/* printf("table %s\n", state->table2); */
}

void print_states() {
	int i;
	for (i = 0; i < head; i++)
		print_state(&states[i]);
}


/* basic environment */

void yyerror(char *msg) {
	fprintf(stderr, "%s at %s\n", msg, yytext);
}

int main() {
	int result = 0;

	bzero(states, sizeof (t_state) * SIZE_STATES);
	current = &states[0];
	current_proplist = &current->table1;

	result = yyparse();
	if (!result)
		print_states();

	return result;
}
