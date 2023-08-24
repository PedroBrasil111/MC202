#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

p_fila criar_fila(int len) {
    /*Cria uma fila de tamanho len*/
    p_fila fila;
    fila = malloc(sizeof(struct fila));
    fila->vetor = malloc(len * sizeof(char));
    fila->ini = fila->fim = fila->ocup = 0;
    fila->len = len;
    return fila;
}

void enfileira(p_fila fila, char *str) {
    /*Enfileira uma string na fila*/
    for (int i = 0; str[i] != '\0'; i++) {
        fila->vetor[fila->fim] = str[i]; //insere no fim
        fila->fim = (fila->fim + 1) % fila->len;
        fila->ocup++;
    }
}

char desenfileira(p_fila fila) {
    /*Desenfileira um char da fila*/
    char c = fila->vetor[fila->ini]; //guarda char do início p/ retornar
    fila->ini = (fila->ini + 1) % fila->len;
    fila->ocup--;
    return c;
}

void print_fila(p_fila fila) {
    /*Imprime a string na fila*/
    for (int i = 0; i < fila->ocup; i++)
        printf("%c", fila->vetor[(fila->ini + i) % fila->len]);
}

void destruir_fila(p_fila fila) {
    /*Libera a fila*/
    free(fila->vetor);
    free(fila);
}