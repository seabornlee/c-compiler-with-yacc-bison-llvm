#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

Ast* newNode(char* type, char* value, Ast* left, Ast* right) {
    Ast* ast = (Ast*) malloc(sizeof(Ast));
    ast->type = type;
    ast->value = value;
    ast->left = left;
    ast->right = right;
    return ast;
}

void printIndent(int depth) {
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
}

void showAst(Ast* ast, int depth) {
    printIndent(depth);
    printf("<%s, %s>\n", ast->type, ast->value);
    if (ast->left) {
        showAst(ast->left, depth + 1);
    }

    if (ast->right) {
        showAst(ast->right, depth + 1);
    }
}

void freeAst(Ast* ast) {
    if (ast == NULL) {
        return;
    }

    freeAst(ast->left);
    freeAst(ast->right);
    free(ast);
}