#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

/* Cria e retorna o grafo com numP pontos de recebimento, 
 * numC centros de distribuição e p_grafo->alocado == alocado */
p_grafo criar_grafo(int numP, int numC, int alocado) {
    int i;
    p_grafo g = malloc(sizeof(struct Grafo));
    g->n = numP + numC; //número total de vértices do grafo
    g->alocado = alocado;
    g->adjacencia = malloc(g->alocado * sizeof(p_no));
    for (i = 0; i < g->n; i++)
        g->adjacencia[i] = NULL;
    return g;
}

/* Insere uma aresta entre nome1 e nome2 */
void inserir_aresta(p_grafo grafo, int nome1, int nome2) {
    grafo->adjacencia[nome1] = inserir_na_lista(grafo->adjacencia[nome1], nome2);
    grafo->adjacencia[nome2] = inserir_na_lista(grafo->adjacencia[nome2], nome1);
}

/* Remove a aresta entre nome1 e nome2 */
void remover_aresta(p_grafo grafo, int nome1, int nome2) {
    grafo->adjacencia[nome1] = remover_da_lista(grafo->adjacencia[nome1], nome2);
    grafo->adjacencia[nome2] = remover_da_lista(grafo->adjacencia[nome2], nome1);
}

/* Retorna 1 se num1 e num2 forem adjacentes, 0 caso contrário */
int adjacentes(p_grafo g, int nome1, int nome2) {
    for (p_no v = g->adjacencia[nome1]; v != NULL; v = v->prox)
        //v itera sobre a lista de adjacência de nome1
        if (v->num == nome2) 
            return 1;
    return 0;
}

/* Retorna um vetor 'pai' tal que pai[i] é o pai de i
 * na direção de menor distância do vértice nome */
int *busca_em_largura(p_grafo g, int nome) {
    //Copiado do slide com alguns ajustes
    int v, w; //iteram sobre os vértices
    int *pai = malloc(g->n * sizeof(int));
    int *visitado = calloc(g->n, sizeof(int));
    p_fila f = criar_fila(g->n);
    for (v = 0; v < g->n; v++)
        pai[v] = -1;
    enfileira(f, nome);
    pai[nome] = nome;
    visitado[nome] = 1;
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

/* Retorna a menor distância entre ini e fim */
int distancia(p_grafo g, int ini, int fim) {
    int dist = 1, *pai = busca_em_largura(g, ini);
    //assumindo que ini != fim, então dist >= 1
    for (int i = pai[fim]; i != ini; i = pai[i])
        //conta quantos vértices há entre ini e fim pelo menor caminho
        dist++;
    free(pai);
    return dist;
}

/* Adiciona um centro de distribuição com aresta para nome e todos os vizinhos de nome */
void adicionar_centro_distrib(p_grafo g, int nome) {
    g->adjacencia[g->n] = NULL; //novo centro tem nome g->n (última posição disponível)
    for (p_no v = g->adjacencia[nome]; v != NULL; v = v->prox)
        //itera sobre os vizinhos de nome para criar arestas para g->n
        inserir_aresta(g, g->n, v->num);
    inserir_aresta(g, g->n, nome); //aresta entre g->n e nome
    g->n++;
}

/* Ordena o vetor dados de tamanho igual a len */
void insertion_sort(int *dados, int len) {
    int i, j, aux;
    for (i = 1; i < len; i++) {
        aux = dados[i];
        for (j = i; j > 0 && aux < dados[j-1]; j--)
            dados[j] = dados[j-1];
        dados[j] = aux;
    }
}

/* Imprime os vizinhos do vértice nome na mesma linha */
void imprimir_vizinhos(p_grafo g, int nome) {
    int i, len = 0, *vizinhos = malloc(g->n * sizeof(int));
    //vizinhos guarda os vizinhos do vértice, len é o tamanho de vizinhos
    for (p_no v = g->adjacencia[nome]; v != NULL; v = v->prox) {
        //v itera sobre os vizinhos de nome para guardá-los
        vizinhos[len] = v->num;
        len++;
    }
    insertion_sort(vizinhos, len); //ordena vizinhos
    for (i = 0; i < len - 1; i++)
        printf("%d ", vizinhos[i]);
    printf("%d\n", vizinhos[i]);
    free(vizinhos);
}

/* Libera o grafo */
void liberar_grafo(p_grafo grafo) {
    for (int i = 0; i < grafo->n; i++)
        liberar_lista(grafo->adjacencia[i]);
    free(grafo);
}