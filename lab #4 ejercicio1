#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void findLargestLine(int **matrix, int size, int *result) {
    int *base = *(matrix + 0);   
    int total = size * size;
    int max_seq = 0;
    int cur_seq = 0;

    for (int i = 0; i < total; i++) {
        if (*(base + i) == 1) {
            cur_seq++;
            if (cur_seq > max_seq) {
                max_seq = cur_seq;
            }
        } else {
            cur_seq = 0;
        }
    }
    *result = max_seq;
}

void allocateMatrix(int ***matrix, int size) {
    
    *matrix = (int **)malloc(size * sizeof(int *));
    if (*matrix == NULL) {
        fprintf(stderr, "Error: malloc fallo para arreglo de filas.\n");
        exit(1);
    }

    int *block = (int *)malloc(size * size * sizeof(int));
    if (block == NULL) {
        fprintf(stderr, "Error: malloc fallo para bloque de datos.\n");
        free(*matrix);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        *(*matrix + i) = block + i * size;
    }
}

void fillMatrix(int **matrix, int size) {
    int *base = *(matrix + 0);
    int total = size * size;
    for (int i = 0; i < total; i++) {
        *(base + i) = rand() % 2;
    }
}

void printMatrix(int **matrix, int size) {
    printf("Matriz (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void freeMatrix(int **matrix, int size) {
    
    free(*(matrix + 0));
    free(matrix);
}

int main(void) {
    int size, largestLine;
    int **matrix = NULL;

    srand((unsigned int)time(NULL));

    printf("Ingrese el tamano de la matriz: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Error: tamano invalido.\n");
        return 1;
    }

    allocateMatrix(&matrix, size);
    fillMatrix(matrix, size);
    printMatrix(matrix, size);
    findLargestLine(matrix, size, &largestLine);
    freeMatrix(matrix, size);

    printf("El tamano de la secuencia de 1s mas grande es: %d\n", largestLine);
    return 0;
}
