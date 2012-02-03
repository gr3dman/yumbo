#include <stdio.h>

#include "meml.h"

extern int yyparse();

void print_xml_escaped(char *s) {
	for (; *s; s++) {
		switch (*s) {
			case '<':
				printf("&lt;");
				break;
			case '>':
				printf("&gt;");
				break;
			default:
				printf("%c", *s);
		}
	}
}

void print_table(proplist_t *props) {
	char *name = props->val;
	printf("\t%s [shape=record label=\"{", name);
	print_xml_escaped(name);
	for (props = props->next; props; props = props->next) {
		if (!props->line)
			printf("|%s", props->val);
	}
	printf("}\"];\n");
}

void print_cardinal(char *label, enum cardinal card) {
	switch (card) {
		case CARD_ONE:
			printf("%s=1", label);
			break;
		case CARD_MANY:
			printf("%s=\"*\"", label);
			break;
		case CARD_ZERO_ONE:
			printf("%s=\"0..1\"", label);
			break;
		case CARD_ZERO_MANY:
			printf("%s=\"0..*\"", label);
			break;
	}
}

void print_tail(state_t *state) {
	if (state->dotted || state->attribute
			|| state->cardinal1 || state->cardinal2) {

		printf(" [");

		if (state->dotted)
			printf("style=dashed");

		if (state->attribute) {
			if (state->dotted)
				printf(",");
			printf("dir=both,arrowtail=");
			switch (state->attribute) {
				case ATTR_REVERSE_ARROW:
					printf("normal");
					break;
				case ATTR_AGGREGATE:
					printf("odiamond");
					break;
				case ATTR_COMPOSE:
					printf("diamond");
					break;
				case ATTR_INHERIT:
					printf("empty,arrowhead=none");
			}
		}

		if (state->cardinal1) {
			if (state->dotted || state->attribute)
				printf(",");
			print_cardinal("taillabel", state->cardinal1);
		}

		if (state->cardinal2) {
			if (state->dotted || state->attribute || state->cardinal1)
				printf(",");
			print_cardinal("headlabel", state->cardinal2);
		}
		printf("]");
	}
}

void print_edge(state_t *state) {
	char *tab1, *tab2;
	tab1 = state->table1->val;
	tab2 = state->table2->val;
	printf("\t%s -> %s", tab1, tab2);
	print_tail(state);
	printf(";\n");
}

void print_state(state_t *state) {
	print_table(state->table1);
	if (state->table2) {
		print_table(state->table2);
		print_edge(state);
	}
}

void print_header() {
	printf("digraph {\n");
}

void print_footer() {
	printf("}\n");
}

void print_graph() {
	int i;

	print_header();
	for (i = 0; states[i].table1; i++)
		print_state(&states[i]);
	print_footer();
}

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

int main() {
	int result;
	init();

	result = yyparse();
	if (!result)
		print_graph();
	return result;
}
