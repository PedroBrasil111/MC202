#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

#define MAX 100

int main() {
    p_mapa mapa = criar_mapa();  //raiz da árvore mapa
    p_vis visita = criar_visita();  //raiz da árvore viista
    int numOp, data, pista, dataIni, dataFim;
    //numOp: quantidade de operações, data: data de inserção na árvore visita;
    //pista: pista da árvore visita, dataIni/Fim: intervalo de datas dos relatórios
    char comando[20], *nome = malloc(MAX * sizeof(char)), *nomeRemov = malloc(MAX * sizeof(char));
    //comando: operação a ser realizada, nome: nome da cidade inserida,
    //nomeRemov: nome removido da árvore visita
    scanf("%d", &numOp);
    for (int i = 0; i < numOp; i++) {
        scanf(" %s", comando);
        if (strcmp(comando, "insere_visita") == 0){
            scanf(" %s %d %d", nome, &data, &pista);
            mapa = inserir_mapa(mapa, nome);
            visita = inserir_visita(visita, data, pista, nome);
        } else if (strcmp(comando, "exclui_visita") == 0) {
            scanf("%d", &data);
            visita = remover_visita(visita, data, nomeRemov);
            mapa = remover_mapa(mapa, nomeRemov);
        } else if (strcmp(comando, "relatorio_data") == 0) {
            scanf("%d %d", &dataIni, &dataFim);
            printf("--VISITAS--\n");
            relatorio_data(visita, dataIni, dataFim);
        } else if (strcmp(comando, "relatorio_pista") == 0) {
            scanf("%d %d", &dataIni, &dataFim);
            printf("--PISTAS--\n");
            relatorio_pista(visita, dataIni, dataFim);
        }
    }
    free(nomeRemov);
    free(nome);
    destruir_mapa(mapa);
    destruir_visita(visita);
    return 0;
}