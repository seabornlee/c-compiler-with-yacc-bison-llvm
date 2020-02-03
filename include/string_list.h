#ifndef STRING_LIST_H_
#define STRING_LIST_H_

#include "utils.h"

struct listNode {
    char* value;
    struct listNode* next;
};
typedef struct listNode ListNode;

struct stringList {
    ListNode* head;
    ListNode* last;
    int sizeOfValues;
};

typedef struct stringList StringList;

StringList* initStringList();
void add(StringList* list, char* string);
char* toString(StringList* list);
bool isEmpty(StringList* list);

#endif  //  STRING_LIST_H_