#include <stdlib.h>
#include <string.h>
#include "string_list.h"

StringList *initStringList() {
    return (StringList *) malloc(sizeof(StringList));
}

ListNode *newListNode(char *string) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = string;
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
    char *buffer = (char *) malloc(list->sizeOfValues);

    ListNode* node = getFirstOf(list);
    while (node) {
        strcat(buffer, node->value);
        node = node->next;
    }
    return buffer;
}
