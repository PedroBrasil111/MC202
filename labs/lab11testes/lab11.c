#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

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