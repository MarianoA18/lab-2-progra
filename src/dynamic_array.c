#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>

DynamicArray *da_create(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }

    DynamicArray *arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para DynamicArray\n");
        exit(EXIT_FAILURE);
    }

    arr->data = (int *)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para los datos\n");
        free(arr);
        exit(EXIT_FAILURE);
    }

    arr->size = 0;
    arr->capacity = initial_capacity;

    return arr;
}

static void da_resize(DynamicArray *arr) {
    size_t new_capacity = arr->capacity * 2;
    int *new_data = (int *)realloc(arr->data, new_capacity * sizeof(int));

    if (new_data == NULL) {
        fprintf(stderr, "Error: no se pudo redimensionar el arreglo\n");
        exit(EXIT_FAILURE);
    }

    arr->data = new_data;
    arr->capacity = new_capacity;
}

void da_add(DynamicArray *arr, int value) {
    if (arr == NULL) return;

    if (arr->size == arr->capacity) {
        da_resize(arr);
    }

    arr->data[arr->size] = value;
    arr->size++;
}

void da_remove_at(DynamicArray *arr, size_t index) {
    if (arr == NULL || index >= arr->size) {
        fprintf(stderr, "Error: indice fuera de rango en da_remove_at\n");
        return;
    }

    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
}

int da_get(const DynamicArray *arr, size_t index, int *out_value) {
    if (arr == NULL || index >= arr->size || out_value == NULL) {
        return 0;
    }

    *out_value = arr->data[index];
    return 1;
}

void da_print(const DynamicArray *arr) {
    if (arr == NULL) return;

    printf("[");
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i != arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void da_destroy(DynamicArray *arr) {
    if (arr == NULL) return;
    free(arr->data);
    free(arr);
}