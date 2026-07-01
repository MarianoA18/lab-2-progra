#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int contar_unos_fila(int m[][SIZE], int fila) {
    int contador = 0;
    for (int j = 0; j < SIZE; j++) {
        if (m[fila][j] == 1) {
            contador++;
        }
    }
    return contador;
}

int contar_unos_columna(int m[][SIZE], int col) {
    int contador = 0;
    for (int i = 0; i < SIZE; i++) {
        if (m[i][col] == 1) {
            contador++;
        }
    }
    return contador;
}

int es_identidad(int m[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == j && m[i][j] != 1) return 0;
            if (i != j && m[i][j] != 0) return 0;
        }
    }
    return 1;
}

int tiene_fila_completa(int m[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (contar_unos_fila(m, i) == SIZE) {
            return 1;
        }
    }
    return 0;
}

int tiene_columna_completa(int m[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        if (contar_unos_columna(m, j) == SIZE) {
            return 1;
        }
    }
    return 0;
}

void imprimir_matriz(int m[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void analizar_matriz(int m[][SIZE], const char *titulo) {
    printf("%s:\n", titulo);
    imprimir_matriz(m);
    printf("Es matriz identidad: %s\n", es_identidad(m) ? "si" : "no");
    printf("Tiene fila completa de unos: %s\n", tiene_fila_completa(m) ? "si" : "no");
    printf("Tiene columna completa de unos: %s\n\n", tiene_columna_completa(m) ? "si" : "no");
}

int main(void) {
    int m[SIZE][SIZE] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    analizar_matriz(m, "Matriz ingresada");

    int aleatoria[SIZE][SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            aleatoria[i][j] = rand() % 2;
        }
    }

    analizar_matriz(aleatoria, "Matriz aleatoria");

    return 0;
}
