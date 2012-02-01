#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "meml.h"

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
	current = states = malloc(sizeof (state_t));
	current_proplist = &current->table1;
}

/* parser actions */

void term() {
	current = &states[++myhead];

	current_proplist = &current->table1;
}

void table() {
	current_proplist = &current->table2;
}

void property(char *prop) {
	int len = strlen(prop) + 1;

	*current_proplist = malloc(sizeof (proplist_t));
	bzero(*current_proplist, sizeof (proplist_t));
	(*current_proplist)->val = malloc(len * sizeof (char));
	strncpy((*current_proplist)->val, prop, len);
	trim((*current_proplist)->val);

	current_proplist = &(*current_proplist)->next;
}

void line() {
	*current_proplist = malloc(sizeof (proplist_t));
	bzero(*current_proplist, sizeof(proplist_t));
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
