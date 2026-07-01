#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

DoublyLinkedList *dll_create(void) {
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para DoublyLinkedList\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

static DNode *create_dnode(int value) {
    DNode *node = (DNode *)malloc(sizeof(DNode));
    if (node == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para DNode\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void dll_insert_front(DoublyLinkedList *list, int value) {
    if (list == NULL) return;

    DNode *node = create_dnode(value);
    node->next = list->head;

    if (list->head != NULL) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }

    list->head = node;
}

void dll_insert_back(DoublyLinkedList *list, int value) {
    if (list == NULL) return;

    DNode *node = create_dnode(value);
    node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
}

void dll_insert_at(DoublyLinkedList *list, size_t position, int value) {
    if (list == NULL) return;

    if (position == 0) {
        dll_insert_front(list, value);
        return;
    }

    DNode *current = list->head;
    size_t index = 0;

    while (current != NULL && index < position) {
        current = current->next;
        index++;
    }

    if (current == NULL) {
        dll_insert_back(list, value);
        return;
    }

    DNode *node = create_dnode(value);
    DNode *previous = current->prev;

    node->prev = previous;
    node->next = current;
    current->prev = node;

    if (previous != NULL) {
        previous->next = node;
    } else {
        list->head = node;
    }
}

int dll_remove(DoublyLinkedList *list, int value) {
    if (list == NULL || list->head == NULL) return 0;

    DNode *current = list->head;

    while (current != NULL) {
        if (current->data == value) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                list->head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev;
            }

            free(current);
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int dll_search(const DoublyLinkedList *list, int value) {
    if (list == NULL) return 0;

    DNode *current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void dll_print_forward(const DoublyLinkedList *list) {
    if (list == NULL) return;

    printf("head -> ");
    DNode *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void dll_print_backward(const DoublyLinkedList *list) {
    if (list == NULL) return;

    printf("tail -> ");
    DNode *current = list->tail;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

void dll_destroy(DoublyLinkedList *list) {
    if (list == NULL) return;

    DNode *current = list->head;
    while (current != NULL) {
        DNode *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}