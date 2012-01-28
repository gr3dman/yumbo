#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "meml.h"

static t_state states[SIZE_STATES];
static int head = 0;
static t_state *current;

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

void attribute(enum attribute attr) {
	current->attribute = attr;
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

void print_attribute(enum attribute attr) {
	printf("%s\n", attr == ATTR_ARROW ? "arrow"
			: attr == ATTR_AGGREGATE ? "aggregate"
			: attr == ATTR_COMPOSE ? "compose"
			: "unknown");
}

void print_cardinality(char *fmt, enum cardinal card) {
	printf(fmt, card == CARD_ONE ? "one"
				: card == CARD_MANY ? "many"
				: card == CARD_ZERO_MANY ? "zero or many"
				: "unknown");
}

void print_state(t_state *state) {
	printf("table %s\n", state->table1);
	if (state->inherit)
		printf("inherit\n");
	if (state->attribute)
		print_attribute(state->attribute);
	if (state->cardinal1)
		print_cardinality("%s\n", state->cardinal1);
	if (state->cardinal2)
		print_cardinality("%s\n", state->cardinal2);
	if (state->table2)
		printf("table %s\n", state->table2);
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
