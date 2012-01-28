%{
#include <string.h>

#include "y.tab.h"
#include "meml.h"

extern yylval;

%}
%option noyywrap

label [a-zA-Z]+(\ *[a-zA-Z])*
other [\[\],01\.\*\-<>\+]
%%
{label}		{
				strncpy(word, yytext, SIZE_WORD);
				return T_Word;
			}
{other}		{ return yytext[0]; }
.			{ /* ignore */ }
