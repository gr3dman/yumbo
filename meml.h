#define SIZE_WORD 256

char word[SIZE_WORD];

enum attribute {
	ATTR_ARROW = 1,
	ATTR_INHERIT = 2,
	ATTR_AGGREGATE = 4,
	ATTR_COMPOSE = 8
};

typedef struct {
	char table1[SIZE_WORD];
	char table2[SIZE_WORD];

	char label[SIZE_WORD];

	char cardinal1[SIZE_WORD];
	char cardinal2[SIZE_WORD];

	int bidi, dotted;

	enum attribute attribute;
} t_state;

void yyerror(char *msg);
