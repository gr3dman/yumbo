#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "meml.h"

extern char *yytext;
extern int yyparse();


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

void print_proplist(proplist_t *proplist) {
	proplist_t *pl;
	int props;
	for (pl = proplist, props = 0; pl; pl = pl->next, props++)
		if (pl->line)
			printf("line\n");
		else
			printf("%s %s\n", props ? "property" : "table", pl->val);
}

void print_state(state_t *state) {
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
	for (i = 0; states[i].table1; i++)
		print_state(&states[i]);
}


/* basic environment */

void yyerror(char *msg) {
	fprintf(stderr, "%s at %s\n", msg, yytext);
}

int main() {
	int result = 0;

	init();
	result = yyparse();
	if (!result)
		print_states();

	return result;
}
