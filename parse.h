#ifndef PARSE_H
#define PARSE_H

#define SIZE_PROP 256
#define SIZE_STATES 128

typedef struct proplist {
	int line;
	char *val;
	struct proplist *next;
} proplist_t;

enum attribute {
	ATTR_NONE = 0,
	ATTR_REVERSE_ARROW = 1,
	ATTR_AGGREGATE = 2,
	ATTR_COMPOSE = 4,
	ATTR_INHERIT = 8
};

enum cardinal {
	CARD_NONE = 0,
	CARD_ONE = 1,
	CARD_MANY = 2,
	CARD_ZERO_ONE = 4,
	CARD_ZERO_MANY = 8
};

typedef struct {
	proplist_t *table1, *table2;

	int arrow, dotted;

	enum cardinal cardinal1, cardinal2;
	enum attribute attribute;
} state_t;

char prop[SIZE_PROP];
state_t states[SIZE_STATES];

void init();

void pair();
void table();

void property(char *prop);
void line();

void attribute(enum attribute attr);
void inherit();
void arrow();
void dotted();

void cardinal1(enum cardinal card);
void cardinal2(enum cardinal card);

#endif
