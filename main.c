#include <stdio.h>
#include <string.h>
#include "dynamic_array.h"
#include "linked_list.h"
#include "doubly_linked_list.h"
#include "stack.h"

static void demo_dynamic_array(void) {
    printf("========================================\n");
    printf(" DEMO: Arreglo Dinamico\n");
    printf("========================================\n");

    DynamicArray *arr = da_create(2);

    printf("Creando arreglo con capacidad inicial 2.\n");

    da_add(arr, 10);
    da_add(arr, 20);
    da_add(arr, 30);
    printf("Despues de agregar 10, 20, 30: ");
    da_print(arr);

    int value;
    if (da_get(arr, 1, &value)) {
        printf("Elemento en el indice 1: %d\n", value);
    }

    printf("Eliminando elemento en el indice 0...\n");
    da_remove_at(arr, 0);
    printf("Arreglo resultante: ");
    da_print(arr);

    da_destroy(arr);
    printf("Arreglo destruido.\n\n");
}

static void demo_linked_list(void) {
    printf("========================================\n");
    printf(" DEMO: Lista Enlazada Simple\n");
    printf("========================================\n");

    LinkedList *list = ll_create();

    ll_insert_back(list, 1);
    ll_insert_back(list, 2);
    ll_insert_back(list, 3);
    printf("Despues de insertar 1, 2, 3 al final: ");
    ll_print_forward(list);

    ll_insert_front(list, 0);
    printf("Despues de insertar 0 al inicio: ");
    ll_print_forward(list);

    ll_insert_at(list, 2, 99);
    printf("Despues de insertar 99 en la posicion 2: ");
    ll_print_forward(list);

    printf("Buscando el valor 99: %s\n", ll_search(list, 99) ? "encontrado" : "no encontrado");

    printf("Eliminando el valor 99...\n");
    ll_remove(list, 99);
    printf("Lista resultante: ");
    ll_print_forward(list);

    ll_destroy(list);
    printf("Lista destruida.\n\n");
}

static void demo_doubly_linked_list(void) {
    printf("========================================\n");
    printf(" DEMO: Lista Doblemente Enlazada\n");
    printf("========================================\n");

    DoublyLinkedList *list = dll_create();

    dll_insert_back(list, 1);
    dll_insert_back(list, 2);
    dll_insert_back(list, 3);
    printf("Despues de insertar 1, 2, 3 al final: ");
    dll_print_forward(list);

    dll_insert_front(list, 0);
    printf("Despues de insertar 0 al inicio: ");
    dll_print_forward(list);

    dll_insert_at(list, 2, 99);
    printf("Despues de insertar 99 en la posicion 2: ");
    dll_print_forward(list);

    printf("Impresion hacia atras: ");
    dll_print_backward(list);

    printf("Buscando el valor 99: %s\n", dll_search(list, 99) ? "encontrado" : "no encontrado");

    printf("Eliminando el valor 99...\n");
    dll_remove(list, 99);
    printf("Lista resultante (adelante): ");
    dll_print_forward(list);
    printf("Lista resultante (atras): ");
    dll_print_backward(list);

    dll_destroy(list);
    printf("Lista destruida.\n\n");
}

static void demo_stack(void) {
    printf("========================================\n");
    printf(" DEMO: Stack\n");
    printf("========================================\n");

    Stack *stack = stack_create();

    printf("Stack vacio? %s\n", stack_is_empty(stack) ? "si" : "no");

    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    printf("Despues de push 10, 20, 30.\n");

    int value;
    if (stack_peek(stack, &value)) {
        printf("Peek (tope actual): %d\n", value);
    }

    if (stack_pop(stack, &value)) {
        printf("Pop: %d\n", value);
    }

    if (stack_peek(stack, &value)) {
        printf("Nuevo tope tras el pop: %d\n", value);
    }

    printf("Stack vacio? %s\n", stack_is_empty(stack) ? "si" : "no");

    stack_destroy(stack);
    printf("Stack destruido.\n\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        demo_dynamic_array();
        demo_linked_list();
        demo_doubly_linked_list();
        demo_stack();
        printf("Todas las demostraciones finalizaron correctamente.\n");
        return 0;
    }

    if (strcmp(argv[1], "array") == 0) {
        demo_dynamic_array();
    } else if (strcmp(argv[1], "list") == 0) {
        demo_linked_list();
    } else if (strcmp(argv[1], "dlist") == 0) {
        demo_doubly_linked_list();
    } else if (strcmp(argv[1], "stack") == 0) {
        demo_stack();
    } else {
        printf("Uso: %s [array|list|dlist|stack]\n", argv[0]);
        printf("Sin argumentos, ejecuta todas las demostraciones.\n");
        return 1;
    }

    return 0;
}
