%{
#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

void yyerror(const char* msg);
int yylex(void);
%}

%define parse.error verbose
%token INCLUDE EOP

%union {
  char* sValue;
  struct ast* pAst;
}

%token<sValue> ID

%type <pAst> Program Include
%%
Program: Include  { $$ = $1; }
| Program EOP {
		showAst($1);
		exit(0);
 	      }
;

Include: '#' INCLUDE '<' ID '.' ID '>' { $$ = newIncludeStatement($4); }
;
%%

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
