#include <stdio.h>
#include "./parser.tab.h"
#include "./ast.h"
#define bool int

void printTokens() {
    enum yytokentype token;
    while ((token = yylex()) != EOP)
        printf("%d\n", token);
}

int main(int argc, char* argv[]) {
    extern FILE* yyin;
    yyin = fopen(argv[1], "r");

    bool isDebugMode = argc == 3;
    if (isDebugMode) {
        printTokens();
    } else {
        extern Ast* astRoot;
        yyparse();
        showAst(astRoot, 0);
        freeAst(astRoot);
    }

    fclose(yyin);
    return 0;
}