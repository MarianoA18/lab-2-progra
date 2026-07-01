#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(void) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para Stack\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

void stack_push(Stack *stack, int value) {
    if (stack == NULL) return;

    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    if (node == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para StackNode\n");
        exit(EXIT_FAILURE);
    }

    node->data = value;
    node->next = stack->top;
    stack->top = node;
}

int stack_pop(Stack *stack, int *out_value) {
    if (stack == NULL || stack->top == NULL) {
        return 0;
    }

    StackNode *node = stack->top;

    if (out_value != NULL) {
        *out_value = node->data;
    }

    stack->top = node->next;
    free(node);

    return 1;
}

int stack_peek(const Stack *stack, int *out_value) {
    if (stack == NULL || stack->top == NULL) {
        return 0;
    }

    if (out_value != NULL) {
        *out_value = stack->top->data;
    }

    return 1;
}

int stack_is_empty(const Stack *stack) {
    if (stack == NULL) return 1;
    return stack->top == NULL;
}

void stack_destroy(Stack *stack) {
    if (stack == NULL) return;

    StackNode *current = stack->top;
    while (current != NULL) {
        StackNode *next = current->next;
        free(current);
        current = next;
    }

    free(stack);
}
