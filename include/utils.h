#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>

#define bool int

bool equals(char *stringOne, char *stringTwo);

char *replace(char *origin, char *target, char *with);

char *concat(char *stringOne, char *stringTwo);

#endif  // UTILS_H