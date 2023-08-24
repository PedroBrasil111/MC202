#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* Cria uma fila vazia de tamanho len */
p_fila criar_fila(int len) {
    p_fila f = malloc(sizeof(struct Fila));
    f->v = malloc(len * sizeof(int));
    f->len = len;
    f->ini = f->fim = 0;
    return f;
}

/* Enfileira num na fila*/
void enfileira(p_fila f, int num) {
    f->v[f->fim] = num; //insere no fim
    f->fim = (f->fim + 1) % f->len;
}

/* Retorna 1 se a fila estiver vazia, 0 caso contrário */
int fila_vazia(p_fila f) {
    if (f->ini == f->fim)
        return 1;
    return 0;
}

/* Desenfileira um número da fila e o retorna */
int desenfileira(p_fila f) {
    int num = f->v[f->ini]; //guarda para retornar
    f->ini = (f->ini + 1) % f->len;
    return num;
}

/* Libera a fila */
void liberar_fila(p_fila f) {
    free(f->v);
    free(f);
}