%{
#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

void yyerror(const char* msg);
int yylex(void);
%}

%define parse.error verbose

%token INCLUDE EOP INT CHAR ASSIGN

%union {
  char* sValue;
  struct ast* pAst;
}

%token<sValue> ID
%token<sValue> STRING

%type <pAst> Program Include FuncDefinition Signature Params Body Type Statement Declaration Expression
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

Body: '{' Statement '}' { $$ = newNode("Statements", NULL, $2, NULL); }
;

Statement: Declaration ASSIGN Expression ';' { $$ = newNode("Statement", "=", $1, $3); }
;

Expression: STRING { $$ = newNode("String", $1, NULL, NULL); }
;

Declaration: Type ID { $$ = newNode("Declaration", $2, $1, NULL); }
| Type ID '[' ']' { $$ = newNode("DeclarationArray", $2, $1, NULL); }
;

Type: INT	{ $$ = newNode("Type", "int", NULL, NULL); }
| CHAR '*'	{ $$ = newNode("Type", "char*", NULL, NULL); }
;

Params: Declaration ',' Declaration { $$ = newNode("Params", NULL, $1, $3); }
;
%%

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
