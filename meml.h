#define SIZE_WORD 256

char word[SIZE_WORD];

enum attribute {
	ATTR_NONE = 0,
	ATTR_ARROW = 1,
	ATTR_INHERIT = 2,
	ATTR_AGGREGATE = 4,
	ATTR_COMPOSE = 8
};

enum cardinal {
	CARD_NONE = 0,
	CARD_ONE = 1,
	CARD_MANY = 2,
	CARD_ZERO_MANY = 4
};

typedef struct {
	char *table1, *table2;

	int dotted, inherit;

	enum cardinal cardinal1, cardinal2;
	enum attribute attribute;
} t_state;

void yyerror(char *msg);
