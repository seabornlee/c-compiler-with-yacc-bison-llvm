#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>

#define bool int

bool equals(char *stringOne, char *stringTwo);

char *replace(char *origin, char *target, char *with);

char *concat(char *stringOne, char *stringTwo);

char *newString(int length);

char *checkedMalloc(size_t size);
#endif  // UTILS_H