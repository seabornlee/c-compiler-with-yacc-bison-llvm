%code requires {
int yylex();
}

%{
#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

void yyerror(const char* msg);
%}

%define parse.error verbose

%token INCLUDE EOP INT CHAR ASSIGN

%union {
  char* sValue;
  struct ast* node;
}

%token<sValue> ID
%token<sValue> STRING

%type <node> Program Include FuncDefinition Signature
 Params Body Type Statements Statement Declaration
 Expression CallStatement Parameters Parameter AssignStatement
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

Body: '{' Statements '}' { $$ = newNode("Body", NULL, $2, NULL); }
;

Statements: Statement Statements { $$ = newNode("List", NULL, $1, $2); }
| Statement { $$ = $1; }
;

Statement: AssignStatement { $$ = $1; }
| CallStatement ';' { $$ = $1; }
;

AssignStatement: Declaration ASSIGN Expression ';' { $$ = newNode("Assign", "=", $1, $3); }
;

CallStatement: ID '(' Parameters ')' { $$ = newNode("Call", $1, $3, NULL); }
;

Parameters: Parameter ',' Parameters  { $$ = newNode("List", NULL, $1, $3); }
| Parameter { $$ = $1; }
;

Parameter: STRING { $$ = newNode("String", $1, NULL, NULL); }
| ID { $$ = newNode("ID", $1, NULL, NULL); }
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
