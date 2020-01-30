#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

Ast* newNode(char* type) {
    Ast* ast = (Ast*) malloc(sizeof(Ast));
    ast->type = type;
    return ast;
}

Ast* newIncludeStatement(char* libName) {
    Ast* ast = newNode("include");
    ast->value = libName;
    return ast;
}

void showAst(Ast* ast) {
    printf("--Ast start:-----------------------\n");
    printf("<%s, %s>\n", ast->type, ast->value);
    printf("--Ast end:-------------------------\n");
}