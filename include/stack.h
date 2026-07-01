/* Modulo: Stack. Implementa push, pop, peek e isEmpty usando una lista enlazada interna. */
#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

Stack *stack_create(void);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack, int *out_value);
int stack_peek(const Stack *stack, int *out_value);
int stack_is_empty(const Stack *stack);
void stack_destroy(Stack *stack);

#endif
