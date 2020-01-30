#include <stdio.h>
#include "./parser.tab.h"
#include "./ast.h"

int main(int argc, char* argv[]) {
    yyparse();
    return 0;
}