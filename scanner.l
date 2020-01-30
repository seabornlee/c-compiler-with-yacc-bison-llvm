%option noyywrap

%{
#include "parser.tab.h"
%}

%%
"int"       { return INT; }
"char"       { return CHAR; }

"#" |
"<" |
">" |
"," |
"*" |
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
";" |
"."         { return yytext[0]; }
"include"     { return INCLUDE; }
[a-zA-Z]+   { yylval.sValue = strdup(yytext); return ID; }
\"[^\"]*\"  { yylval.sValue = strdup(yytext); return STRING; }
"="         { yylval.sValue = strdup(yytext); return ASSIGN; };
[ ]         {}
\n          {}
<<EOF>>     { return EOP; }
%%
