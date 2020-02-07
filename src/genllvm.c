#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "string_list.h"
#include "utils.h"

char *toCode(Ast *node) {
    return "";
}

char *removeQuote(char *string) {
    int length = strlen(string) - 2;
    char *buffer = (char *) malloc(length);
    memcpy(buffer, &string[1], length);
    return buffer;
}

void visitNode(Ast *node, StringList *buffer, StringList *stringConstants) {
    if (equals(node->type, "String")) {
        add(stringConstants, removeQuote(node->value));
        return;
    }

    add(buffer, toCode(node));
    if (node->left) {
        visitNode(node->left, buffer, stringConstants);
    }

    if (node->right) {
        visitNode(node->right, buffer, stringConstants);
    }

}

int lengthOf(char *string) {
    char *result = replace(string, "\\0A", "$");
    return strlen(result) + 1;
}

char *genStringConstantCode(char *string, int index) {
    char *formattedString = replace(string, "\\n", "\\0A");
    char *template = "@.str%s = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1\n";
    char *suffix = (char *) malloc(10);
    memset(suffix, 0, 10);
    if (index > 0) {
        sprintf(suffix, ".%d", index);
    }

    int size = strlen(suffix) + strlen(template) + strlen(formattedString);
    char *code = (char *) malloc(size);
    memset(code, 0, size);
    sprintf(code, template, suffix, lengthOf(formattedString), formattedString);
    return code;
}

char *genStringConstantsCode(StringList *list) {
    StringList *buffer = initStringList();
    int index = 0;

    ListNode *node = list->head;
    while (node) {
        add(buffer, genStringConstantCode(node->value, index));
        node = node->next;
        index++;
    }

    char *code = toString(buffer);
    free(buffer);
    return code;
}

char *concat(char *stringOne, char *stringTwo) {
    size_t size = strlen(stringOne) + strlen(stringTwo);
    char *buffer = (char *) malloc(size);
    memset(buffer, 0, size);
    sprintf(buffer, "%s%s", stringOne, stringTwo);
    free(stringOne);
    free(stringTwo);
    return buffer;
}

char *genLLVMCode(Ast *ast) {
    StringList *buffer = initStringList();
    StringList *stringConstants = initStringList();
    visitNode(ast, buffer, stringConstants);
    char *constantsCode = genStringConstantsCode(stringConstants);
    char *code = concat(constantsCode, toString(buffer));
    free(buffer);
    free(stringConstants);
    return code;
}
