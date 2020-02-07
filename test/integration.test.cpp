#include "gtest/gtest.h"

extern "C" {
    #include "compiler.h"
    #include "string_list.h"
}

static const int SIZE = 1024;

char *readContent(char *filePath) {
    StringList *list = initStringList();
    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("Can not read file: %s", filePath);
        exit(1);
    }

    char buffer[SIZE];
    while (fgets(buffer, SIZE, file) != NULL)
        add(list, strdup(buffer));
    char *text = toString(list);
    fclose(file);
    return text;
}

TEST(Compiler, shouldCompileToLLVMCode) {
    ASSERT_STREQ(
            compileToLLVMCode("../../test/resources/hello.c"),
            readContent("../../test/resources/hello.ll"));
}