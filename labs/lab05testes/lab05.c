#include <stdio.h>
#include <string.h>
#include "ultron.h"

int main() {
    int numOp;
    char operacao[4], eixo;
    //eixo: 'L'/'C', para operações nas linhas/colunas
    Matriz mat;
    mat = leMatriz();
    scanf("%d", &numOp);
    for (int i = 0; i < numOp; i++) {
        scanf("%s %c", operacao, &eixo);
        if (eixo == 'L' && strcmp(operacao, "IN") == 0) {
            mat = insereLinha(mat);
        } else if (eixo == 'L' && strcmp(operacao, "OUT") == 0) {
            mat = removeLinha(mat);
        } else if (eixo == 'C' && strcmp(operacao, "IN") == 0) {
            mat = insereColuna(mat);
        } else if (eixo == 'C' && strcmp(operacao, "OUT") == 0) {
            mat = removeColuna(mat);
        }
        printMatriz(mat);
    }
    printf("COMBINACAO MATRICIAL FINALIZADA!\n");
    destroiMatriz(mat);
    return 0;
}