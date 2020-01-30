#ifndef AST_H_
#define AST_H_

typedef struct ast {
    char* type;
    char* value;
} Ast;

Ast* newNode(char* type);
Ast* newIncludeStatement(char* libName);
void showAst(Ast* ast);

#endif // AST_H_