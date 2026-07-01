/* Modulo: Lista Doblemente Enlazada. Implementa insercion, eliminacion, busqueda e impresion en ambas direcciones. */
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
} DoublyLinkedList;

DoublyLinkedList *dll_create(void);
void dll_insert_front(DoublyLinkedList *list, int value);
void dll_insert_back(DoublyLinkedList *list, int value);
void dll_insert_at(DoublyLinkedList *list, size_t position, int value);
int dll_remove(DoublyLinkedList *list, int value);
int dll_search(const DoublyLinkedList *list, int value);
void dll_print_forward(const DoublyLinkedList *list);
void dll_print_backward(const DoublyLinkedList *list);
void dll_destroy(DoublyLinkedList *list);

#endif
