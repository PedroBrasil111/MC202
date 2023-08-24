#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra.h"

int main() {
    p_cobra cobra = cria_cobra();
    int **mat, numLin, numCol, result = 0, x, y, aux = 0;
    //x, y: usadas para ler posições da fruta e da cobra
    //aux: possibilita imprimir apenas após leitura das posições iniciais
    char operacao[6]; //Guarda a leitura do usuário
    scanf("%d %d", &numLin, &numCol);
    mat = cria_matriz(numLin, numCol);
    while (result == 0) {
        scanf("%s", operacao);
        if (strcmp(operacao, "FRUTA") == 0) {
            scanf("%d %d", &x, &y);
            insere_fruta(mat, x, y);
        } else if (strcmp(operacao, "COBRA") == 0) {
            scanf("%d %d", &x, &y);
            insere_no(cobra, x, y);
            result = resultado_movimento(cobra, mat, numLin, numCol);
        } else {  //w, a, s, d
            movimento(cobra, numLin, numCol, operacao[0]);
            result = resultado_movimento(cobra, mat, numLin, numCol);
        }
        if (aux)
            print_matriz(mat, numLin, numCol);
        aux = 1; //Após o primeiro ciclo começa a imprimir
    }
    if (result == 1)
        printf("YOU WIN\n");
    else
        printf("GAME OVER\n");
    destruir_cobra(cobra);
    destruir_matriz(mat, numLin);
}