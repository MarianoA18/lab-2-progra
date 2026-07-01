#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

DynamicArray *da_create(size_t initial_capacity);
void da_add(DynamicArray *arr, int value);
void da_remove_at(DynamicArray *arr, size_t index);
int da_get(const DynamicArray *arr, size_t index, int *out_value);
void da_print(const DynamicArray *arr);
void da_destroy(DynamicArray *arr);

#endif