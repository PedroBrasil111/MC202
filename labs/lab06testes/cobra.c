#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"

p_cobra cria_cobra() {
    /*Cria a cobra sem nós*/
    p_cobra cobra = malloc(sizeof(struct cobra));
    cobra->cabeca = cobra->cauda = NULL;
    return cobra;
}

void insere_no(p_cobra cobra, int x, int y) {
    /*Insere um nó ao início (cabeça) da cobra, dados x e y da nova posição*/
    p_no novo = malloc(sizeof(struct no)); //Nova cabeça
    if (cobra->cabeca == NULL) { //Se a cobra estiver vazia
        novo->prox = NULL;
        cobra->cauda = novo;
    } else {
        novo->prox = cobra->cabeca;
        cobra->cabeca->ant = novo;
    }
    cobra->cabeca = novo;
    novo->ant = NULL;
    novo->x = x;
    novo->y = y;
}

void remove_no(p_cobra cobra) {
    /*Remove a cauda da cobra*/
    p_no cauda = cobra->cauda; //Variável auxiliar para guardar a cauda
    if (cauda != cobra->cabeca) {
        cobra->cauda = cauda->ant; //Alteração da cauda
        cobra->cauda->prox = NULL;
        free(cauda);
    }
}

void destruir_cobra(p_cobra cobra) {
    /*Libera a cobra*/
    p_no prox;
    while (cobra->cabeca != NULL) {
        prox = cobra->cabeca->prox;
        free(cobra->cabeca);
        cobra->cabeca = prox;
    }
    free(cobra);
}

int **cria_matriz(int numLin, int numCol) {
    /*Dados número de linhas e de colunas, cria uma matriz e a retorna*/
    int **mat = malloc(numLin * sizeof(int *));
    for (int i = 0; i < numLin; i++) {
        mat[i] = malloc(numCol * sizeof(int));
        for (int j = 0; j < numCol; j++)
            mat[i][j] = 0;
    }
    return mat;
}

void print_matriz(int **mat, int numLin, int numCol) {
    /*Imprime a matriz do jogo*/
    for (int i = 0; i < numLin; i++) {
        for (int j = 0; j < numCol; j++) {
            if (mat[i][j] == 0) //Posição vazia
                printf("_ ");
            else if (mat[i][j] == 1) //Cobra
                printf("# ");
            else //Fruta
                printf("* ");
        }
        printf("\n");
    }
    printf("\n");
}

void destruir_matriz(int **mat, int numLin) {
    /*Libera a matriz*/
    for (int i = 0; i < numLin; i++)
        free(mat[i]);
    free(mat);
}

void insere_fruta(int **mat, int x_fruta, int y_fruta) {
    /*Insere a fruta na matriz dada sua posição*/
    mat[x_fruta][y_fruta] = -1;
}

void movimento(p_cobra cobra, int numLin, int numCol, char comando) {  
    /*Dado um comando de movimento (w, a, s, d), cria a nova cabeça da cobra,
    numLin e numCol são as informações da matriz do jogo*/
    insere_no(cobra, cobra->cabeca->x, cobra->cabeca->y);
    //Criação da nova cabeça com mesma posição da anterior, para então ser atualizada
    if (comando == 'w') { //Move para cima
        cobra->cabeca->x--;
        if (cobra->cabeca->x < 0) //Estoura limite superior
            cobra->cabeca->x = numLin - 1;
    } else if (comando == 'a') { //Move para a esquerda
        cobra->cabeca->y--;
        if (cobra->cabeca->y < 0) //Estoura limite à esquerda
            cobra->cabeca->y = numCol - 1;
    } else if (comando == 's') { //Move para baixo
        cobra->cabeca->x = (cobra->cabeca->x + 1) % numLin; //"%" p/ considerar os limites
    } else if (comando == 'd') { //Move para a direita
        cobra->cabeca->y = (cobra->cabeca->y + 1) % numCol;
    }
}

int atualiza_jogo(p_cobra cobra, int **mat, int numLin, int numCol) {
    /*Atualiza a cobra e a matriz do jogo.
    Retorna 0 se o jogo deve continuar, -1 se deve encerrar com derrota*/
    int result = 0, *valor = &(mat[cobra->cabeca->x][cobra->cabeca->y]);
    //valor: valor na posição da cabeca. Tomando caminho p/ não reescrever
    if (*valor == 0) { //Posição vazia: remoção da cauda
        mat[cobra->cauda->x][cobra->cauda->y] = 0;
        remove_no(cobra);
        *valor = 1; //Atualização da posição da cabeça
    } else if (*valor == -1) { //Cobra encontra a fruta: cauda é mantida
        *valor = 1; 
    } else if (*valor == 1) { //Parte da cobra já está na posição
        result = -1; //Derrota
    }
    return result;
}

int resultado_movimento(p_cobra cobra, int **mat, int numLin, int numCol) {
    /*Chamada deve ser feita após o movimento (mudança da posição da cabeça).
    Dada a matriz do jogo, retorna 0 se o jogo deve continuar,
    1 se deve encerrar com vitória e -1 se deve encerrar com derrota*/
    int result = atualiza_jogo(cobra, mat, numLin, numCol);
    if (result != -1) {
        result = 1; //Assume-se vitória inicialmente
        for (int i = 0; i < numLin && result; i++)
            for (int j = 0; j < numCol && result; j++)
                if (mat[i][j] != 1)
                    result = 0; //Caso encontre uma posição não ocupada, o jogo deve seguir
    }
    return result;
}