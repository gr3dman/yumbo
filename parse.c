#include <stdlib.h>
#include <string.h>

#include "parse.h"

int myhead = 0;

static state_t *current;
static proplist_t **current_proplist;

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

void init() {
	current = states;
	current_proplist = &current->table1;
}

/* parser actions */

void pair() {
	current = &states[++myhead];

	current_proplist = &current->table1;
}

void table() {
	current_proplist = &current->table2;
}

void property(char *prop) {
	int len = strlen(prop) + 1;

	*current_proplist = calloc(1, sizeof (proplist_t));
	(*current_proplist)->val = calloc(len, sizeof (char));
	strncpy((*current_proplist)->val, prop, len);
	trim((*current_proplist)->val);

	current_proplist = &(*current_proplist)->next;
}

void line() {
	*current_proplist = calloc(1, sizeof (proplist_t));
	(*current_proplist)->line = 1;

	current_proplist = &(*current_proplist)->next;
}

void attribute(enum attribute attr) {
	current->attribute = attr;
}

void inherit() {
	current->attribute = ATTR_INHERIT;
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
