#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "genllvm.h"

char *compileToLLVMCode(char *filePath) {
    extern FILE* yyin;
    yyin = fopen(filePath, "r");
    if (!yyin) {
        printf("Can not read file: %s\n", filePath);
        exit(1);
    }

    extern Ast* astRoot;
    yyparse();
    showAst(astRoot, 0);
    char* code = genLLVMCode(astRoot);
    freeAst(astRoot);
    fclose(yyin);
    return code;
}