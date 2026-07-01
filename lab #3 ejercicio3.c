#include <stdio.h>
#include <math.h>

#define MAX_SENSORES 10

typedef enum { NORMAL, ALERTA, FALLO } EstadoSensor;

typedef struct {
    int id;
    float valor;
    EstadoSensor estado;
} Lectura;

EstadoSensor clasificar(float valor) {
    if (valor >= 40.0f && valor <= 60.0f) {
        return NORMAL;
    } else if ((valor >= 20.0f && valor < 40.0f) ||
               (valor > 60.0f && valor <= 80.0f)) {
        return ALERTA;
    } else {
        return FALLO;
    }
}

const char *estado_a_cadena(EstadoSensor e) {
    switch (e) {
        case NORMAL: return "NORMAL";
        case ALERTA: return "ALERTA";
        case FALLO:  return "FALLO";
        default:     return "DESCONOCIDO";
    }
}

int contar_estado(Lectura s[], int n, EstadoSensor e) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].estado == e) {
            contador++;
        }
    }
    return contador;
}

int lectura_extrema(Lectura s[], int n) {
    int idx = 0;
    float max_dist = fabsf(s[0].valor - 50.0f);

    for (int i = 1; i < n; i++) {
        float dist = fabsf(s[i].valor - 50.0f);
        if (dist > max_dist) {
            max_dist = dist;
            idx = i;
        }
    }
    return idx;
}

int main(void) {
    Lectura sensores[MAX_SENSORES];

    printf("=== Ingreso de lecturas de sensores ===\n");
    for (int i = 0; i < MAX_SENSORES; i++) {
        printf("\nSensor %d de %d:\n", i + 1, MAX_SENSORES);
        printf("  Identificador: ");
        scanf("%d", &sensores[i].id);
        printf("  Valor        : ");
        scanf("%f", &sensores[i].valor);
        sensores[i].estado = clasificar(sensores[i].valor);
    }

    printf("\n%-10s %-12s %-10s\n", "ID", "Valor", "Estado");
    printf("%-10s %-12s %-10s\n", "----------", "------------", "----------");
    for (int i = 0; i < MAX_SENSORES; i++) {
        printf("%-10d %-12.2f %-10s\n",
               sensores[i].id,
               sensores[i].valor,
               estado_a_cadena(sensores[i].estado));
    }

    printf("\nResumen de estados:\n");
    printf("  NORMAL : %d\n", contar_estado(sensores, MAX_SENSORES, NORMAL));
    printf("  ALERTA : %d\n", contar_estado(sensores, MAX_SENSORES, ALERTA));
    printf("  FALLO  : %d\n", contar_estado(sensores, MAX_SENSORES, FALLO));

    int idx = lectura_extrema(sensores, MAX_SENSORES);
    printf("\nLectura mas extrema (mas alejada de 50.0):\n");
    printf("  ID: %d  |  Valor: %.2f  |  Estado: %s\n",
           sensores[idx].id,
           sensores[idx].valor,
           estado_a_cadena(sensores[idx].estado));

    return 0;
}

