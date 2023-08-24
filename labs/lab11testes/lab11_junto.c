#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no *p_no;

struct no {
    int num; //nome/número do nó
    p_no prox;
};

typedef struct Grafo *p_grafo;

struct Grafo {
    p_no *adjacencia;
    int n, alocado;
};

// INICIO FILA
typedef struct Fila *p_fila;

struct Fila {
    int *v;
    int ini, fim, len;
};

p_fila criar_fila(int len) {
    p_fila f = malloc(sizeof(struct Fila));
    f->v = malloc(len * sizeof(int));
    f->len = len;
    f->ini = f->fim = 0;
    return f;
}

void enfileira(p_fila f, int num) {
    f->v[f->fim] = num; //insere no fim
    f->fim = (f->fim + 1) % f->len;
}

int fila_vazia(p_fila f) {
    if (f->ini == f->fim)
        return 1;
    return 0;
}

int desenfileira(p_fila f) {
    int num = f->v[f->ini];
    f->ini = (f->ini + 1) % f->len;
    return num;
}

void liberar_fila(p_fila f) {
    free(f->v);
    free(f);
}
// FIM FILA

p_grafo criar_grafo(int numP, int numC, int alocado) {
    int i;
    p_grafo g = malloc(sizeof(struct Grafo));
    g->n = numP + numC;
    g->alocado = alocado;
    g->adjacencia = malloc(g->alocado * sizeof(p_no));
    for (i = 0; i < g->n; i++)
        g->adjacencia[i] = NULL;
    return g;
}

void liberar_lista(p_no lista) {
    if (lista != NULL) {
        liberar_lista(lista->prox);
        free(lista);
    }
}

void liberar_grafo(p_grafo grafo) {
    for (int i = 0; i < grafo->n; i++) {
        liberar_lista(grafo->adjacencia[i]);
    }
    free(grafo);
}

p_no inserir_na_lista(p_no lista, int num) {
    p_no novo = malloc(sizeof(struct no));
    novo->num = num;
    novo->prox = lista;
    return novo;
}

p_no remover_da_lista(p_no lista, int num) {
    p_no ant = lista, atual;
    if (lista == NULL) return NULL;
    if (lista->num == num) {
        atual = lista->prox;
        free(lista);
        return atual;
    }
    atual = lista->prox;
    while (atual != NULL) {
        if (atual->num == num) {
            ant->prox = atual->prox;
            free(atual);
            return lista;
        }
        ant = atual;
        atual = atual->prox;        
    }
    return lista; //não achou
}

void inserir_aresta(p_grafo grafo, int nome1, int nome2) {
    grafo->adjacencia[nome1] = inserir_na_lista(grafo->adjacencia[nome1], nome2);
    grafo->adjacencia[nome2] = inserir_na_lista(grafo->adjacencia[nome2], nome1);
}

void remover_aresta(p_grafo grafo, int nome1, int nome2) {
    grafo->adjacencia[nome1] = remover_da_lista(grafo->adjacencia[nome1], nome2);
    grafo->adjacencia[nome2] = remover_da_lista(grafo->adjacencia[nome2], nome1);
}


int adjacentes(p_grafo g, int num1, int num2) {
    for (p_no v = g->adjacencia[num1]; v != NULL; v = v->prox)
        if (v->num == num2)
            return 1;
    return 0;
}

int *busca_em_largura(p_grafo g, int num) {
    int v, w;
    int *pai = malloc(g->n * sizeof(int));
    int *visitado = calloc(g->n, sizeof(int));
    p_fila f = criar_fila(g->n);
    for (v = 0; v < g->n; v++)
        pai[v] = -1;
    enfileira(f, num);
    pai[num] = num;
    visitado[num] = 1;
    while(!fila_vazia(f)) {
        v = desenfileira(f);
        for (w = 0; w < g->n; w++)
            if (adjacentes(g, v, w) && !visitado[w]) {
                visitado[w] = 1; /*evita repetição na fila*/
                pai[w] = v;
                enfileira(f, w);
            }
    }
    liberar_fila(f);
    free(visitado);
    return pai;
}

int distancia(p_grafo g, int ini, int fim) {
    // assumindo que ini != fim, então dist >= 1
    int dist = 1, *pai = busca_em_largura(g, ini);
    for (int i = pai[fim]; i != ini; i = pai[i])
        dist++;
    free(pai);
    return dist;
}

void adicionar_centro_distrib(p_grafo g, int num) {
    g->adjacencia[g->n] = NULL;
    inserir_aresta(g, g->n, num);
    for (p_no v = g->adjacencia[num]; v != NULL; v = v->prox) {
        if (v->num != g->n)
            inserir_aresta(g, g->n, v->num);
    }
    g->n++;
}

void insertion_sort(int *dados, int len) {
    int i, j, aux;
    for (i = 1; i < len; i++) {
        aux = dados[i];
        for (j = i; j > 0 && aux < dados[j-1]; j--)
            dados[j] = dados[j-1];
        dados[j] = aux;
    }
}

void imprimir_vizinhos(p_grafo g, int num) {
    int i = 0, j, *vizinhos = malloc(g->n * sizeof(int));
    for (p_no v = g->adjacencia[num]; v != NULL; v = v->prox) {
        vizinhos[i] = v->num;
        i++;
    }
    insertion_sort(vizinhos, i);
    //quicksort(vizinhos, 0, i);
    for (j = 0; j < i - 1; j++)
        printf("%d ", vizinhos[j]);
    printf("%d\n", vizinhos[j]);
    free(vizinhos);
}

#define MAX 50

int main() {
    int numP, numC, numArestas, numOp, nome1, nome2, distMax, dist;
    /* numP/numC: número de pontos de receb./centros de distrib.;
     * numOp: núm. de operações; nome1, nome2: para leitura dos vértices
     * distMin: distância máxima para inserção de centro de distrib. na operação D */
    char comando; //Comando ('R' ou 'D')
    p_grafo grafo;
    scanf("%d %d", &numP, &numC);
    grafo = criar_grafo(numP, numC, MAX);
    scanf("%d", &numArestas);
    for (int i = 0; i < numArestas; i++) {
        scanf("%d %d", &nome1, &nome2);
        inserir_aresta(grafo, nome1, nome2);
    }
    printf("GRAFO AMZ CONSTRUIDO!\n");
    scanf("%d", &numOp);
    for (int i = 0; i < numOp; i++) {
        scanf(" %c %d %d", &comando, &nome1, &nome2);
        if (comando == 'R') { //remoção de aresta entre nome1 e nome2
            remover_aresta(grafo, nome1, nome2);
            printf("ARESTA %d -> %d REMOVIDO\n", nome1, nome2);
        } else if (comando == 'D') { //cálculo da distância entre nome1 e nome2
            scanf("%d", &distMax);
            dist = distancia(grafo, nome1, nome2);
            printf("DISTANCIA %d -> %d = %d\n", nome1, nome2, dist);
            if (dist > distMax) {
                adicionar_centro_distrib(grafo, nome2);
                //centro adicionado tem nome (grafo->n - 1)
                printf("%d ADICIONADO E CONECTADO A ", grafo->n - 1);
                imprimir_vizinhos(grafo, grafo->n - 1);
            }
        }
    }
    free(grafo);
    return 0;
}