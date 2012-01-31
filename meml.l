%{
#include <string.h>

#include "y.tab.h"
#include "meml.h"

%}
%option noyywrap
%x INTABLE

property [^(\|;|\])]+
%%
<INTABLE>{property}	{
				strncpy(prop, yytext, SIZE_PROP);
				return T_Property;
			}
<INITIAL>"["	{ BEGIN(INTABLE); return yytext[0]; }
<INTABLE>"]"	{ BEGIN(INITIAL); return yytext[0]; }
<INTABLE>.		{ return yytext[0]; }
<INITIAL>" "	{ /* ignore */ }
.				{ return yytext[0]; }
