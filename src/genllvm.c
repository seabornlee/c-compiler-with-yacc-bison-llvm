#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "string_list.h"
#include "utils.h"

char *genTypeCode(char *type) {
    if (equals(type, "int"))
        return "i32";
    return "i8*";
}

char *genTypeCodeFromDeclaration(Ast *declarationNode) {
    char *typeCode = genTypeCode(declarationNode->left->value);

    if (equals(declarationNode->type, "Array")) {
        return concat(typeCode, "*");
    }

    return typeCode;
}

char *genParamsTypeCode(Ast *paramsNode) {
    char *template = "%s, %s";
    char *buffer = newString(10);
    sprintf(buffer, template, genTypeCodeFromDeclaration(paramsNode->left), genTypeCodeFromDeclaration(paramsNode->right));
    return buffer;
}

char *generateFunctionDefinitionCode(Ast *node) {
    char *name = node->left->value;
    char *returnType = genTypeCode(node->value);
    char *paramsType = genParamsTypeCode(node->left->left);
    char *template = "\ndefine %s @%s(%s) {\n}";
    char *buffer = newString(50);
    sprintf(buffer, template, returnType, name, paramsType);
    return buffer;
}

char *toCode(Ast *node) {
    if (equals(node->type, "Function")) {
        return generateFunctionDefinitionCode(node);
    }
    return "";
}

char *removeQuote(char *string) {
    int length = strlen(string) - 2;
    char *buffer = newString(length);
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
    char *suffix = newString(10);
    if (index > 0) {
        sprintf(suffix, ".%d", index);
    }

    int size = strlen(suffix) + strlen(template) + strlen(formattedString);
    char *code = newString(size);
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
