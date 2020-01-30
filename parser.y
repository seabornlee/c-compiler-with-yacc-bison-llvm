%{
#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

void yyerror(const char* msg);
int yylex(void);
%}

%define parse.error verbose

%token INCLUDE EOP INT CHAR

%union {
  char* sValue;
  struct ast* pAst;
}

%token<sValue> ID

%type <pAst> Program Include FuncDefinition Signature Params Param Body Type
%%
Program: Include FuncDefinition { $$ = newNode("Program", NULL, $1, $2); }
| Program EOP {
		showAst($1, 0);
		exit(0);
 	      }
;

Include: '#' INCLUDE '<' ID '.' ID '>' { $$ = newNode("Include", $4, NULL, NULL); }
;

FuncDefinition: Signature Body { $$ = newNode("Function", NULL, $1, $2); }
;

Signature: Type ID '(' Params ')' { $$ = newNode("Signature", $2, $4, NULL); }
;

Body: '{' '}' { $$ = newNode("Statements", NULL, NULL, NULL); }
;

Type: INT	{ $$ = newNode("Type", "int", NULL, NULL); }
| CHAR		{ $$ = newNode("Type", "char", NULL, NULL); }
;

Params: Param ',' Param { $$ = newNode("Params", NULL, $1, $3); }
;

Param: Type ID	{ $$ = newNode("Param", $2, $1, NULL); }
| Type '*' ID '[' ']' { $$ = newNode("PointerParamArray", $3, $1, NULL); }
;
%%

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
