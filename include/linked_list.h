#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

LinkedList *ll_create(void);
void ll_insert_front(LinkedList *list, int value);
void ll_insert_back(LinkedList *list, int value);
void ll_insert_at(LinkedList *list, size_t position, int value);
int ll_remove(LinkedList *list, int value);
int ll_search(const LinkedList *list, int value);
void ll_print_forward(const LinkedList *list);
void ll_destroy(LinkedList *list);

#endif