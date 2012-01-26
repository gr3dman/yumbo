%{
#include <string.h>

#include "y.tab.h"
#include "meml.h"

extern yylval;

%}
%option noyywrap
%%
[a-zA-Z]+	{
				strncpy(word, yytext, SIZE_WORD);
				return T_Word;
			}
[0-9]+		{ yylval = atoi(yytext); return T_Number; }
[\[\],]		{ return yytext[0]; }
->			{ return T_Arrow; }
--			{ return T_Line; }
.			{ /* ignore */ }
