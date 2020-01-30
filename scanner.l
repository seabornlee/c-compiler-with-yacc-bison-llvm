%option noyywrap

%{
#include "parser.tab.h"
%}

%%
"#" |
"<" |
">" |
"."         { return yytext[0]; }
"include"     { return INCLUDE; }
[a-zA-Z]+   { yylval.sValue = strdup(yytext); return ID; }
[ ]         {}
<<EOF>>     { return EOP; }
%%

