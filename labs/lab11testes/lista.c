#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Insere um nó na lista, com no->num = num */
p_no inserir_na_lista(p_no lista, int num) {
    p_no novo = malloc(sizeof(struct no));
    novo->num = num;
    novo->prox = lista;
    return novo;
}

/* Remove o nó com no->num == num da lista */
p_no remover_da_lista(p_no lista, int num) {
    p_no ant, atual; //variáveis para iterar sobre a lista
    if (lista == NULL) return NULL;
    if (lista->num == num) { //primeiro nó contém num
        atual = lista->prox;
        free(lista);
        return atual; //lista->prox vira o primeiro nó da lista
    }
    ant = lista; //ant: nó anterior a atual
    atual = lista->prox;
    while (atual != NULL) {
        if (atual->num == num) {
            ant->prox = atual->prox; //ajuste dos ponteiros
            free(atual); //remoção do nó
            break;
        }
        ant = atual;
        atual = atual->prox;
    }
    return lista;
}

/* Libera a lista */
void liberar_lista(p_no lista) {
    if (lista != NULL) {
        liberar_lista(lista->prox);
        free(lista);
    }
}