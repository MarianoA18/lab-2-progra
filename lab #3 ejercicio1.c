#include <stdio.h>

int potencia(int base, int exp) {
    int resultado = 1;
    while (exp > 0) {
        resultado = resultado * base;
        exp = exp - 1;
    }
    return resultado;
}

int es_par(int n) {
    return (n % 2 == 0) ? 1 : 0;
}

int main(void) {
    int base, exp, resultado;

    do {
        printf("Ingrese la base (distinta de cero): ");
        scanf("%d", &base);
        if (base == 0) {
            printf("Error: la base no puede ser cero. Intente de nuevo.\n");
        }
    } while (base == 0);

    do {
        printf("Ingrese el exponente (numero entero no negativo): ");
        scanf("%d", &exp);
        if (exp < 0) {
            printf("Error: el exponente debe ser no negativo. Intente de nuevo.\n");
        }
    } while (exp < 0);

    resultado = potencia(base, exp);
    printf("\n%d^%d = %d\n", base, exp, resultado);

    if (es_par(resultado)) {
        printf("El resultado es PAR.\n");
    } else {
        printf("El resultado es IMPAR.\n");
    }

    return 0;
}
