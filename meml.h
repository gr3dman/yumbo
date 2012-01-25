#define SIZE_WORD 256

char word[SIZE_WORD];

enum attribute {
	ATTR_ARROW = 1,
	ATTR_INHERIT = 2,
	ATTR_DOTTED = 4,
	ATTR_AGGREGATE = 8,
	ATTR_COMPOSE = 16,
	ATTR_REVERSE_ARROW = 32
};

typedef struct {
	char table1[SIZE_WORD];
	char table2[SIZE_WORD];

	enum attribute attribute;
	char label[SIZE_WORD];

	char cardinal1[SIZE_WORD];
	char cardinal2[SIZE_WORD];
} t_state;

void yyerror(char *msg);
