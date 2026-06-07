#include <stdio.h>
#include <stdlib.h>

unsigned char *read_pgm(const char *filename,
                        int *width, int *height, int *max_val) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: no se pudo abrir %s\n", filename);
        return NULL;
    }

    char magic[3];
    if (fscanf(fp, "%2s", magic) != 1 || magic[0] != 'P' || magic[1] != '2') {
        fprintf(stderr, "Error: formato PGM invalido (se esperaba P2).\n");
        fclose(fp);
        return NULL;
    }

    int c = fgetc(fp);
    while (c == '#') {
        while (c != '\n' && c != EOF) c = fgetc(fp);
        c = fgetc(fp);
    }
    ungetc(c, fp);

    if (fscanf(fp, "%d %d %d", width, height, max_val) != 3) {
        fprintf(stderr, "Error: encabezado PGM malformado.\n");
        fclose(fp);
        return NULL;
    }

    int total = (*width) * (*height);
    unsigned char *pixels = (unsigned char *)malloc(total * sizeof(unsigned char));
    if (pixels == NULL) {
        fprintf(stderr, "Error: malloc fallo para pixeles.\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < total; i++) {
        int val;
        if (fscanf(fp, "%d", &val) != 1) {
            fprintf(stderr, "Error: datos de pixeles insuficientes.\n");
            free(pixels);
            fclose(fp);
            return NULL;
        }
        *(pixels + i) = (unsigned char)val;
    }

    fclose(fp);
    return pixels;
}

void apply_threshold(unsigned char *pixels, int total, int threshold) {
    unsigned char *p = pixels;
    unsigned char *end = pixels + total;
    while (p != end) {
        *p = (*p >= (unsigned char)threshold) ? 255 : 0;
        p++;
    }
}

unsigned char *make_negative(unsigned char *pixels, int total) {
    unsigned char *neg = (unsigned char *)malloc(total * sizeof(unsigned char));
    if (neg == NULL) {
        fprintf(stderr, "Error: malloc fallo para negativo.\n");
        return NULL;
    }

    unsigned char *src = pixels;
    unsigned char *dst = neg;
    unsigned char *end = pixels + total;
    while (src != end) {
        *dst = 255 - *src;
        src++;
        dst++;
    }
    return neg;
}

void write_pgm(const char *filename, unsigned char *pixels,
               int width, int height, int max_val) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: no se pudo crear %s\n", filename);
        return;
    }

    fprintf(fp, "P2\n%d %d\n%d\n", width, height, max_val);

    int total = width * height;
    for (int i = 0; i < total; i++) {
        fprintf(fp, "%d", *(pixels + i));
        
        if ((i + 1) % width == 0) {
            fprintf(fp, "\n");
        } else {
            fprintf(fp, " ");
        }
    }

    fclose(fp);
}

void print_stats(unsigned char *original,
                 unsigned char *thresholded, int total) {
    long long sum = 0;
    int whites = 0;
    int blacks = 0;

    unsigned char *po = original;
    unsigned char *pt = thresholded;
    unsigned char *end = thresholded + total;

    while (pt != end) {
        sum += *po;
        if (*pt == 255) {
            whites++;
        } else {
            blacks++;
        }
        po++;
        pt++;
    }

    printf("--- Estadisticas ---\n");
    printf("Pixeles blancos (umbralizado): %d\n", whites);
    printf("Pixeles negros  (umbralizado): %d\n", blacks);
    printf("Promedio original: %.2f\n", (double)sum / total);
}

int main(void) {
    int width, height, max_val, threshold;
    unsigned char *pixels  = NULL;
    unsigned char *original_copy = NULL;
    unsigned char *negative = NULL;

    pixels = read_pgm("input.pgm", &width, &height, &max_val);
    if (pixels == NULL) {
        return 1;
    }

    int total = width * height;

    original_copy = (unsigned char *)malloc(total * sizeof(unsigned char));
    if (original_copy == NULL) {
        fprintf(stderr, "Error: malloc fallo para copia original.\n");
        free(pixels);
        return 1;
    }
    unsigned char *src = pixels;
    unsigned char *dst = original_copy;
    unsigned char *end = pixels + total;
    while (src != end) {
        *dst = *src;
        src++;
        dst++;
    }

    printf("Ingrese el valor del umbral T (0-%d): ", max_val);
    if (scanf("%d", &threshold) != 1) {
        fprintf(stderr, "Error: umbral invalido.\n");
        free(pixels);
        free(original_copy);
        return 1;
    }

    apply_threshold(pixels, total, threshold);

    negative = make_negative(pixels, total);
    if (negative == NULL) {
        free(pixels);
        free(original_copy);
        return 1;
    }

    write_pgm("output_threshold.pgm", pixels, width, height, max_val);
    write_pgm("output_negative.pgm", negative, width, height, max_val);
    printf("Archivos escritos: output_threshold.pgm, output_negative.pgm\n");

    print_stats(original_copy, pixels, total);

    free(pixels);
    free(original_copy);
    free(negative);

    return 0;
}
