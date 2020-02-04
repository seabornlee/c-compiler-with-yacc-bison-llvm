#ifndef AST_H_
#define AST_H_

typedef struct ast {
    char* type;
    char* value;
    struct ast* left;
    struct ast* right;
} Ast;

Ast* newNode(char* type, char* value, Ast* left, Ast* right);
void showAst(Ast* ast, int depth);
void freeAst(Ast* ast);

#endif // AST_H_