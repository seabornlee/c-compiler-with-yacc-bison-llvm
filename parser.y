%{
#include <stdio.h>
void yyerror(const char* msg);
int yylex(void);
%}

%token EOP

%%

eop: { printf("Parse Complete!\n"); }
;
%%

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
