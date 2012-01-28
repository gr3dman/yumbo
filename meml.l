%{
#include <string.h>

#include "y.tab.h"
#include "meml.h"

extern yylval;

%}
%option noyywrap

label [a-zA-Z]+(\ *[a-zA-Z])*
other [\[\],01\.\*\-<>\+]
aggregate <>
composite \+\+
%%
{label}		{
				strncpy(word, yytext, SIZE_WORD);
				return T_Word;
			}
{aggregate}	{ return T_Aggregate; }
{composite} { return T_Composite; }
{other}		{ return yytext[0]; }
.			{ /* ignore */ }
