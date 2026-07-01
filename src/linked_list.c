#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *ll_create(void) {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para LinkedList\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

static Node *create_node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para Node\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

void ll_insert_front(LinkedList *list, int value) {
    if (list == NULL) return;

    Node *node = create_node(value);
    node->next = list->head;
    list->head = node;
}

void ll_insert_back(LinkedList *list, int value) {
    if (list == NULL) return;

    Node *node = create_node(value);

    if (list->head == NULL) {
        list->head = node;
        return;
    }

    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

void ll_insert_at(LinkedList *list, size_t position, int value) {
    if (list == NULL) return;

    if (position == 0) {
        ll_insert_front(list, value);
        return;
    }

    Node *current = list->head;
    size_t index = 0;

    while (current != NULL && index < position - 1) {
        current = current->next;
        index++;
    }

    if (current == NULL) {
        fprintf(stderr, "Error: posicion fuera de rango en ll_insert_at, se inserta al final\n");
        ll_insert_back(list, value);
        return;
    }

    Node *node = create_node(value);
    node->next = current->next;
    current->next = node;
}

int ll_remove(LinkedList *list, int value) {
    if (list == NULL || list->head == NULL) return 0;

    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL) {
        if (current->data == value) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }

    return 0;
}

int ll_search(const LinkedList *list, int value) {
    if (list == NULL) return 0;

    Node *current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void ll_print_forward(const LinkedList *list) {
    if (list == NULL) return;

    printf("head -> ");
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void ll_destroy(LinkedList *list) {
    if (list == NULL) return;

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}