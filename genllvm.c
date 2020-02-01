#include <string.h>
#include "ast.h"
#include "genllvm.h"
#include "string_list.h"

char *toCode(Ast *node) {
    return node->type;
}

void visitNode(Ast *node, StringList* buffer) {
    add(buffer, toCode(node));
    if (node->left) {
        visitNode(node->left, buffer);
    }

    if (node->right) {
        visitNode(node->right, buffer);
    }
}

char *genLLVMCode(Ast *ast) {
    StringList* buffer = initStringList();
    visitNode(ast, buffer);
    return toString(buffer);
}