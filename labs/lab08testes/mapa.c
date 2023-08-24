#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

/* ÁRVORE MAPA */

/* Cria a árvore mapa sem nós */
p_mapa criar_mapa() {
    return NULL;
}

/* Insere a cidade na árvore mapa */
p_mapa inserir_mapa(p_mapa raiz, char *cidade) {
    p_mapa novo;
    int cmp;  //comparação entre cidade e raiz->cidade
    if (raiz == NULL) {  //cidade deve ser inserida
        novo = malloc(sizeof(struct Mapa));
        novo->qtdeVis = 1;
        novo->cidade = malloc((strlen(cidade) + 1) * sizeof(char));
        strcpy(novo->cidade, cidade);
        novo->esq = novo->dir = novo->pai = NULL;
        printf("ARVORE: MAPA\nCIDADE: %s\nINSERIDO COM SUCESSO!\n####\n", novo->cidade);
        return novo;
    }
    cmp = strcmp(cidade, raiz->cidade);
    if (cmp == 0) {  //cidade já está na árvore
        raiz->qtdeVis++; //adiciona uma visita à cidade
    } else if (cmp < 0) { //cidade < raiz->cidade
        raiz->esq = inserir_mapa(raiz->esq, cidade);
        raiz->esq->pai = raiz;
    } else {  //cidade > raiz->cidade
        raiz->dir = inserir_mapa(raiz->dir, cidade);
        raiz->dir->pai = raiz;
    }
    return raiz;
}

/* Remove um nó da árvore mapa e retorna o nó que ficará na sua posição */
p_mapa substituir_mapa(p_mapa no) {
    p_mapa aux, subst;               //aux será o máx. de no->esq, subst é o nó que susbituirá o nó
    if (no->esq == no->dir) {        //implica que esq == dir == NULL (folha)
        subst = NULL;                //basta remover
    } else if (no->esq == NULL) {    //só possui nó direito
        no->dir->pai = no->pai;
        subst = no->dir;             //substituido pelo nó direito
    } else if (no->dir == NULL) {    //só possui nó esquerdo
        no->esq->pai = no->pai;
        subst = no->esq;             //substituido pelo nó esquerdo
    } else {                         //possui os dois filhos
        aux = no->esq;
        while (aux->dir != NULL)
            aux = aux->dir;          //aux é o máximo de no->esq
        aux->dir = no->dir;          //direita do nó vira direita de aux
        no->dir->pai = aux;
        subst = no->esq;             //substituido pelo nó esquerdo
        no->esq->pai = no->pai;
    }
    free(no->cidade);
    free(no);
    return subst;
}

/* Reduz a quantidade de visitas da cidade na árvore mapa, e a remove se qtdeVis = 0 */
p_mapa remover_mapa(p_mapa raiz, char *cidade) {
    int cmp;  //comparação entre raiz->cidade e cidade
    if (raiz == NULL)
        return NULL;
    cmp = strcmp(cidade, raiz->cidade);
    if (cmp < 0) {  //cidade < raiz->cidade
        raiz->esq = remover_mapa(raiz->esq, cidade);
    } else if (cmp > 0) {  //cidade > raiz->cidade
        raiz->dir = remover_mapa(raiz->dir, cidade);
    } else {  //cmp == 0, encontrou o nó da cidade
        raiz->qtdeVis--;
        printf("CIDADE: %s\nQUANTIDADE DE VISITAS RESTANTES: %d\n####\n", raiz->cidade, raiz->qtdeVis);
        if (raiz->qtdeVis == 0)
            raiz = substituir_mapa(raiz); //remoção do nó
    }
    return raiz;
}

/* Libera a árvore mapa */
void destruir_mapa(p_mapa raiz) {
    if (raiz != NULL) {
        destruir_mapa(raiz->esq);
        destruir_mapa(raiz->dir);
        free(raiz->cidade);
        free(raiz);
    }
}

/* ÁRVORE VISITA */

/* Cria a árvore visitas sem nós */
p_vis criar_visita() {
    return NULL;
}

/* Insere a data na árvore visita */
p_vis inserir_visita(p_vis raiz, int data, int pista, char *cidade) {
    p_vis novo;
    if (raiz == NULL) {  //data deve ser inserida
        novo = malloc(sizeof(struct Visita));
        novo->pista = pista;
        novo->data = data;
        novo->cidade = malloc((strlen(cidade) + 1) * sizeof(char));
        strcpy(novo->cidade, cidade);
        novo->esq = novo->dir = novo->pai = NULL;
        printf("ARVORE: VISITA\nDATA: %d\nCIDADE: %s\nINSERIDO COM SUCESSO!\n####\n", data, cidade);
        return novo;
    }
    if (data < raiz->data) {
        raiz->esq = inserir_visita(raiz->esq, data, pista, cidade);
        raiz->esq->pai = raiz;
    } else {
        raiz->dir = inserir_visita(raiz->dir, data, pista, cidade);
        raiz->dir->pai = raiz;
    }
    return raiz;
}

/* Remove um nó da árvore visita e retorna o nó que ficará na sua posição */
p_vis substituir_visita(p_vis no) {
    p_vis aux, subst;                //aux será o máx. de no->esq, subst é o nó que susbituirá o nó
    if (no->esq == no->dir) {        //implica que esq == dir == NULL (folha)
        subst = NULL;                //basta remover
    } else if (no->esq == NULL) {    //só possui nó direito
        no->dir->pai = no->pai;
        subst = no->dir;             //substituido pelo nó direito
    } else if (no->dir == NULL) {    //só possui nó esquerdo
        no->esq->pai = no->pai;
        subst = no->esq;             //substituido pelo nó esquerdo
    } else {                         //possui os dois filhos
        aux = no->esq;
        while (aux->dir != NULL)
            aux = aux->dir;          //aux é o máximo de no->esq
        aux->dir = no->dir;          //direita do nó vira direita de aux
        no->dir->pai = aux;
        subst = no->esq;             //substituido pelo nó esquerdo
        no->esq->pai = no->pai;
    }
    free(no->cidade);
    free(no);
    return subst;
}

/* Remove o nó referente à data; cidadeRemov: nome da cidade que foi removida */
p_vis remover_visita(p_vis raiz, int data, char *cidadeRemov) {
    //passagem de cidadeRemov para que possa ser alterada na função e usada no main
    if (raiz == NULL)
        return NULL;
    if (data < raiz->data) {
        raiz->esq = remover_visita(raiz->esq, data, cidadeRemov);
    } else if (data > raiz->data) {
        raiz->dir = remover_visita(raiz->dir, data, cidadeRemov);
    } else {  //encontrou o nó a ser removido
        strcpy(cidadeRemov, raiz->cidade);
        raiz = substituir_visita(raiz);
    }
    return raiz;
}

/* Imprime as visitas entre dataIni e dataFim em ordem crescente de data */
void relatorio_data(p_vis raiz, int dataIni, int dataFim) {
    if (raiz != NULL) {
        if (raiz->data > dataFim)  //só precisa buscar à esquerda
            relatorio_data(raiz->esq, dataIni, dataFim);
        else if (raiz->data < dataIni)  //só busca à direita
            relatorio_data(raiz->dir, dataIni, dataFim);
        else {  //está no intervalo
            relatorio_data(raiz->esq, dataIni, dataFim);
            //impressão da esquerda primeiro (ordem crescente)
            printf("DATA: %d\nCIDADE: %s\n####\n", raiz->data, raiz->cidade); 
            relatorio_data(raiz->dir, dataIni, dataFim);
        }
    }
}

/* Imprime as visitas com pista entre dataIni e dataFim em ordem decrescente de data */
void relatorio_pista(p_vis raiz, int dataIni, int dataFim) {
   if (raiz != NULL) {
        if (raiz->data > dataFim)  //só precisa buscar à esquerda
            relatorio_pista(raiz->esq, dataIni, dataFim);
        else if (raiz->data < dataIni)  //só busca à direita
            relatorio_pista(raiz->dir, dataIni, dataFim);
        else {  //está no intervalo
            relatorio_pista(raiz->dir, dataIni, dataFim);
            //impressão da direita primeiro (ordem decrescente)
            if (raiz->pista)  //possui pista
                printf("DATA: %d\nCIDADE: %s\n####\n", raiz->data, raiz->cidade);
            relatorio_pista(raiz->esq, dataIni, dataFim);
        }
   }
}

/* Libera a árvore visita */
void destruir_visita(p_vis raiz) {
    if (raiz != NULL) {
        destruir_visita(raiz->esq);
        destruir_visita(raiz->dir);
        free(raiz->cidade);
        free(raiz);
    }
}