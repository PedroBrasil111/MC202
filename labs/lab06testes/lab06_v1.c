#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cobra *p_cobra;

struct cobra {
    int x, y;
    p_cobra ant, prox;
};

typedef struct matriz *p_matriz;

struct matriz {
    int **dados, numCol, numLin;
};

p_cobra cria_cobra() {
    return NULL;
}

p_cobra insere_cabeca(p_cobra cabeca, int x, int y) {
    /*Insere um nó ao início (cabeça) da cobra, dados x e y da nova posição*/
    p_cobra novo = malloc(sizeof(struct cobra));
    if (cabeca == NULL) {
        novo->prox = NULL;
    } else {
        novo->prox = cabeca;
        cabeca->ant = novo;
    }
    novo->ant = NULL;
    novo->x = x;
    novo->y = y;
    return novo;
}

p_cobra remove_cauda(p_cobra cauda) {
    /*Libera a cauda e retorna a nova cauda*/
    p_cobra nova_cauda = cauda->ant;
    nova_cauda->prox = NULL;
    free(cauda);
    return nova_cauda;
}

void destruir_cobra(p_cobra cabeca) {
    /*Libera os nós da lista recursivamente*/
    if (cabeca == NULL) {
    } else {
        destruir_cobra(cabeca->prox);
        free(cabeca);
    }
}

p_matriz cria_matriz() {
    /*Cria uma matriz com todas as entradas iguais a zero*/
    p_matriz mat = malloc(sizeof(struct matriz));
    scanf("%d %d", &(mat->numLin), &(mat->numCol));
    mat->dados = malloc(mat->numLin * sizeof(int *));
    for (int i = 0; i < mat->numLin; i++) {
        mat->dados[i] = malloc(mat->numCol * sizeof(int));
        for (int j = 0; j < mat->numCol; j++)
            mat->dados[i][j] = 0;
    }
    return mat;
}

void print_matriz(p_matriz mat) {
    /*Imprime a matriz do jogo*/
    for (int i = 0; i < mat->numLin; i++) {
        for (int j = 0; j < mat->numCol; j++) {
            if (mat->dados[i][j] == 0)
                printf("_ ");
            else if (mat->dados[i][j] > 0)
                printf("# ");
            else
                printf("* ");
        }
        printf("\n");
    }
    printf("\n");
}

void destroi_matriz(p_matriz mat) {
    /*Libera a matriz*/
    for (int i = 0; i < mat->numLin; i++)
        free(mat->dados[i]);
    free(mat->dados);
    free(mat);
}

void insere_fruta(p_matriz mat) {
    int x, y;
    scanf("%d %d", &x, &y);
    mat->dados[x][y] = -1;
}

p_cobra atualiza_matriz(p_cobra cabeca, p_cobra cauda, p_matriz mat) {
    int *valor = &(mat->dados[cabeca->x][cabeca->y]); //valor aponta para a entrada na posição da cabeça
    if (*valor == 0) { //cabeça se move a uma posição vazia
        mat->dados[cauda->x][cauda->y] = 0;
        cauda = remove_cauda(cauda);
        *valor = 1;
    } else if (*valor == -1) { //cabeça encontra a fruta
        *valor = 1;
    } else if (*valor == 1) {  //cabeça encontra o corpo da cobra
        *valor = 2;
    }
    return cauda;
}

p_cobra movimento(p_cobra cabeca, p_cobra cauda, p_matriz mat, char *comando) {
    cabeca = insere_cabeca(cabeca, cabeca->x, cabeca->y);
    if (comando[0] == 'w') {
        cabeca->x--;
        if (cabeca->x < 0) //ultrapassa a borda superior
            cabeca->x = mat->numLin - 1;
    } else if (comando[0] == 'a') {
        cabeca->y--;
        if (cabeca->y < 0) //ultrapassa a borda esquerda
            cabeca->y = mat->numCol - 1;
    } else if (comando[0] == 's') {
        cabeca->x = (cabeca->x + 1) % mat->numLin;
    } else if (comando[0] == 'd') {
        cabeca->y = (cabeca->y + 1) % mat->numCol;
    }
    return cabeca;
}

int checa_resultado(p_cobra cabeca, p_matriz mat) {
    int resultado = 1; //0: segue o jogo; 1: vitoria; -1: derrota
    if (mat->dados[cabeca->x][cabeca->y] == 2)
        return -1;
    for (int i = 0; i < mat->numLin && resultado; i++)
        for (int j = 0; j < mat->numCol && resultado; j++)
            if (mat->dados[i][j] != 1)
                resultado = 0;
    return resultado;
}

int main() {
    int resultado = 0, x_inicial, y_inicial, aux = 0;
    char operacao[6];
    p_cobra cabeca, cauda;
    p_matriz mat;
    mat = cria_matriz();
    cabeca = cauda = cria_cobra();
    while (resultado == 0) {
        scanf("%s", operacao);
        if (strcmp(operacao, "FRUTA") == 0) {
            insere_fruta(mat);
        } else if (strcmp(operacao, "COBRA") == 0) {
            scanf("%d %d", &x_inicial, &y_inicial);
            cabeca = cauda = insere_cabeca(cabeca, x_inicial, y_inicial);
            mat->dados[x_inicial][y_inicial] = 1;
        } else {
            cabeca = movimento(cabeca, cauda, mat, operacao);
            cauda = atualiza_matriz(cabeca, cauda, mat);
            resultado = checa_resultado(cabeca, mat);
        }
        if (aux)
            print_matriz(mat);
        aux = 1;
    }
    if (resultado == 1) {
        printf("YOU WIN\n");
    } else {
        printf("GAME OVER\n");
    }
    destruir_cobra(cabeca);
    destroi_matriz(mat);
}