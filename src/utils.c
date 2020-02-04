#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "string_list.h"

bool equals(char* stringOne, char* stringTwo) {
    return !strcmp(stringOne, stringTwo);
}

char *replace(char* origin, char *oldString, char *newString) {
    StringList *list = initStringList();
    int length = strlen(origin);
    int lengthOfOldString = strlen(oldString);
    int start = 0;
    for (int i = 0; i < length; ++i) {
        bool isEqual = !strncmp(&origin[i], oldString, lengthOfOldString);
        if (isEqual) {
            char *buffer = (char *) malloc(i - start);
            memcpy(buffer, &origin[start], i - start);
            add(list, buffer);
            add(list, newString);
            i += lengthOfOldString;
            start = i;
        }
    }

    if (isEmpty(list)) {
        return origin;
    }

    return toString(list);
}
