#define SIZE_STATES 128
#define SIZE_WORD 256

enum attribute {
	ATTR_NONE = 0,
	ATTR_REVERSE_ARROW = 1,
	ATTR_AGGREGATE = 2,
	ATTR_COMPOSE = 4
};

enum cardinal {
	CARD_NONE = 0,
	CARD_ONE = 1,
	CARD_MANY = 2,
	CARD_ZERO_MANY = 4
};

typedef struct {
	char *table1, *table2;

	int arrow, dotted, inherit;

	enum cardinal cardinal1, cardinal2;
	enum attribute attribute;
} t_state;

char word[SIZE_WORD];


void term();
void table(char *name);

void attribute(enum attribute attr);
void inherit();
void arrow();
void dotted();

void cardinal1(enum cardinal card);
void cardinal2(enum cardinal card);

void yyerror(char *msg);
