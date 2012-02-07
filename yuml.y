%{
#include "parse.h"

%}

%token T_Property

%%

Diagram : Term              { pair(); }
        | Diagram ',' Term { pair(); }
        ;

Term : Pair
     | Table
     ;

Pair : Table Relation Table
     ;

Table : '[' PropList ']' { table(); }
      ;

PropList : T_Property               { property(prop); }
         | PropList '|' T_Property  { line(); property(prop); }
         | PropList ';' T_Property  { property(prop); }
         ;

Relation : Cardinal Attr '-' Dotted Arrow Cardinal {
            cardinal1($1);
            attribute($2);
            cardinal2($6);
         }
         | '^' '-' Dotted { inherit(); }
         ;

Cardinal : '1'              { $$ = CARD_ONE; }
         | '*'              { $$ = CARD_MANY; }
         | '0' '.' '.' '1'  { $$ = CARD_ZERO_ONE; }
         | '0' '.' '.' '*'  { $$ = CARD_ZERO_MANY; }
         |                  { $$ = CARD_NONE; }
         ;

Attr : '<' '>'  { $$ = ATTR_AGGREGATE; }
     | '+'      { $$ = ATTR_AGGREGATE; }
     | '+' '+'  { $$ = ATTR_COMPOSE; }
     | '<'      { $$ = ATTR_REVERSE_ARROW; }
     |          { $$ = ATTR_NONE; }
     ;

Dotted : '.' '-'    { dotted(); }
         |
         ;

Arrow : '>'     { arrow(); }
        |
        ;

%%
