#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

p_pilha criar_pilha() {
    /*Cria uma pilha vazia*/
    p_pilha pilha = malloc(sizeof(struct pilha));
    pilha->topo = NULL; //criação sem nó
    return pilha;
}

void adicionar_no(p_pilha pilha) {
    /*Adiciona um nó à pilha*/
    p_no novo = malloc(sizeof(struct no));
    novo->str = malloc(50 * sizeof(char));
    novo->len = 0;
    novo->prox = pilha->topo;
    pilha->topo = novo; //mudança do topo
}

void remover_no(p_pilha pilha) {
    /*Remove um nó da pilha*/
    p_no topo = pilha->topo; //auxiliar para guardar o topo
    pilha->topo = pilha->topo->prox; //mudança do topo
    free(topo->str);
    free(topo);
}

void empilha(p_pilha pilha, char c) {
    /*Adiciona um char ao fim do vetor no topo da pilha*/
    if (pilha->topo == NULL || pilha->topo->len == 50)
        //caso não tenha topo ou o vetor no topo esteja cheio, adiciona um nó
        adicionar_no(pilha);
    pilha->topo->str[pilha->topo->len] = c;
    pilha->topo->len++;
}

void desempilha(p_pilha pilha) {
    /*Remove um char do fim do vetor no topo da pilha*/
    if (pilha->topo->len == 0)
        remover_no(pilha); //remove o nó do topo caso seu vetor esteja vazio
    pilha->topo->len--;
}

void print_pilha_rec(p_no topo) {
    /*Imprime a string contida em uma pilha recursivamente, dado seu topo*/
    if (topo != NULL) {
        print_pilha_rec(topo->prox); //topo é o último nó a ser impresso
        for (int i = 0; i < topo->len; i++)
            printf("%c", topo->str[i]);
    }
}

void print_pilha(p_pilha pilha) {
    /*Imprime a string na pilha*/
    print_pilha_rec(pilha->topo);
}

void destruir_pilha(p_pilha pilha) {
    /*Libera a pilha*/
    while (pilha->topo != NULL)
        remover_no(pilha);
    free(pilha);
}