#include "lista.h"

typedef struct Grafo *p_grafo; //ponteiro para grafo

struct Grafo {
    p_no *adjacencia; //vetor com listas de adjacência
    int n, alocado;
    //n: número de vértices, alocado: espaço alocado por adjacencia
};

/* Cria e retorna o grafo com numP pontos de recebimento, 
 * numC centros de distribuição e p_grafo->alocado == alocado */
p_grafo criar_grafo(int numP, int numC, int alocado);

/* Insere uma aresta entre nome1 e nome2 */
void inserir_aresta(p_grafo grafo, int nome1, int nome2);

/* Remove a aresta entre nome1 e nome2 */
void remover_aresta(p_grafo grafo, int nome1, int nome2);

/* Retorna a menor distância entre ini e fim */
int distancia(p_grafo g, int ini, int fim);

/* Adiciona um centro de distribuição com aresta para nome e todos os vizinhos de nome */
void adicionar_centro_distrib(p_grafo g, int nome);

/* Imprime os vizinhos do vértice nome na mesma linha */
void imprimir_vizinhos(p_grafo g, int nome);

/* Libera o grafo */
void liberar_grafo(p_grafo grafo);