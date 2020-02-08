#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "string_list.h"

char *checkedMalloc(size_t size) {
    char *buffer = (char *) malloc(size);
    if (!buffer) {
        printf("Out of memory.\n");
        exit(1);
    }

    return buffer;
}

char *newString(int length) {
    size_t size = sizeof(char) * length;
    char *buffer = (char *) checkedMalloc(size);
    memset(buffer, 0, size);
    return buffer;
}

bool equals(char* stringOne, char* stringTwo) {
    return !strcmp(stringOne, stringTwo);
}

char *replace(char* origin, char *oldString, char *new) {
    StringList *list = initStringList();
    int length = strlen(origin);
    int lengthOfOldString = strlen(oldString);
    int start = 0;
    for (int i = 0; i < length; ++i) {
        bool isEqual = !strncmp(&origin[i], oldString, lengthOfOldString);
        if (isEqual) {
            char *buffer = newString(i - start);
            memcpy(buffer, &origin[start], i - start);
            add(list, buffer);
            add(list, new);
            i += lengthOfOldString;
            start = i;
        }
    }

    if (isEmpty(list)) {
        return origin;
    }

    return toString(list);
}

char *concat(char *stringOne, char *stringTwo) {
    size_t size = strlen(stringOne) + strlen(stringTwo);
    char *buffer = newString(size);
    sprintf(buffer, "%s%s", stringOne, stringTwo);
    return buffer;
}
