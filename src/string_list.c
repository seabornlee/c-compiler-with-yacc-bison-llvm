#include <stdlib.h>
#include <string.h>
#include "string_list.h"
#include "utils.h"

StringList *initStringList() {
    StringList *list = (StringList *) malloc(sizeof(StringList));
    list->head = NULL;
    list->last = NULL;
    list->sizeOfValues = 0;
    return list;
}

ListNode *newListNode(char *string) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = string;
    node->next = NULL;
    return node;
}

void add(StringList *list, char *string) {
    ListNode *node = newListNode(string);
    if (!list->head) {
        list->head = node;
    }

    if (list->last) {
        list->last->next = node;
    }
    list->last = node;
    list->sizeOfValues += strlen(string);
}

ListNode* getFirstOf(StringList *list) {
    return list->head;
}

char *toString(StringList *list) {
    char *buffer = newString(list->sizeOfValues);
    ListNode* node = getFirstOf(list);
    while (node) {
        strcat(buffer, node->value);
        node = node->next;
    }
    return buffer;
}

bool isEmpty(StringList* list) {
    return list->sizeOfValues == 0;
}