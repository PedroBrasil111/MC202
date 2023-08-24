#include <stdio.h>
#include <stdlib.h>
#include "ultron.h"

Matriz alocaMatriz(int m, int n) {
    /*Aloca uma Matriz com m linhas e n colunas e a retorna*/
    Matriz mat;
    mat.dados = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        mat.dados[i] = malloc(n * sizeof(int));
    mat.linAloc = m;
    mat.colAloc = n;
    return mat;
}

Matriz leMatriz() {
    /*Lê e cria os dados da matriz e a retorna*/
    Matriz mat;
    int m, n; //m linhas, n colunas
    scanf("%d %d", &m, &n);
    mat = alocaMatriz(m, n); //inicialização com espaço alocado = espaço ocupado
    mat.numLin = m;
    mat.numCol = n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &(mat.dados[i][j]));
    return mat;
}

void destroiMatriz(Matriz mat) {
    /*Libera a matriz*/
    for (int i = 0; i < mat.linAloc; i++)
        free(mat.dados[i]);
    free(mat.dados);
}

void printMatriz(Matriz mat) {
    /*Imprime a matriz*/
    for (int i = 0; i < mat.numLin; i++) {
        for (int j = 0; j < mat.numCol; j++)
            printf("%d ", mat.dados[i][j]);
        printf("\n");
    }
    printf("###\n");
}

Matriz realocaLinha(Matriz mat, char operacao) {
    /*Chamada é feita caso mat.numLin < mat.linAloc / 4 depois de realizar remoções,
      ou caso mat.numLin + 1 > mat.linAloc antes de realizar inserções.
      Reduz o número de linhas para a metade no primeiro caso, e dobra no segundo.
      operacao == '+' -> aumenta as linhas; operacao == '-' -> reduz as linhas.*/ 
    Matriz copia;
    copia.numLin = mat.numLin;
    copia.numCol = mat.numCol;
    copia.colAloc = mat.colAloc;
    if (operacao == '+')
        copia.linAloc = 2 * mat.linAloc;
    else
        copia.linAloc = mat.linAloc / 2;
    copia.dados = malloc(copia.linAloc * sizeof(int *));
    for (int i = 0; i < copia.numLin; i++)
        copia.dados[i] = mat.dados[i]; //Copia linhas com dados
    for (int i = copia.numLin; i < copia.linAloc; i++)
        copia.dados[i] = malloc(copia.colAloc * sizeof(int)); //Aloca o resto das linhas
    for (int i = mat.numLin; i < mat.linAloc; i++)
        free(mat.dados[i]); //Libera linhas sem dados de mat
    free(mat.dados);
    return copia;
}

Matriz realocaColuna(Matriz mat, char operacao) {
    /*Chamada é feita caso mat.numCol < mat.colAloc / 4 depois de realizar remoções,
      ou caso mat.numCol + 1 > mat.colAloc antes de realizar inserções.
      Reduz o número de colunas para a metade no primeiro caso, e dobra no segundo.
      operacao == '+' -> aumenta as colunas; operacao == '-' -> reduz as colunas.*/
    Matriz copia;
    copia.numLin = mat.numLin;
    copia.numCol = mat.numCol;
    copia.linAloc = mat.linAloc;
    if (operacao == '+')
        copia.colAloc = 2 * mat.colAloc;
    else
        copia.colAloc = mat.colAloc / 2;
    //Alocando copia:
    copia.dados = malloc(copia.linAloc * sizeof(int *));
    for (int i = 0; i < copia.linAloc; i++)
        copia.dados[i] = malloc(copia.colAloc * sizeof(int));
    //Copiando dados:
    for (int i = 0; i < copia.numLin; i++)
        for (int j = 0; j < copia.numCol; j++)
            copia.dados[i][j] = mat.dados[i][j];
    //Liberando mat:
    for (int i = 0; i < mat.linAloc; i++)
        free(mat.dados[i]);
    free(mat.dados);
    return copia;
}

Matriz insereLinha(Matriz mat) {
    /*Lê e insere uma linha (em ordem crescente) no final da matriz (retorna a matriz modificada)*/
    if (mat.numLin + 1 > mat.linAloc)
        mat = realocaLinha(mat, '+');
    mat.numLin++;
    for (int j = 0; j < mat.numCol; j++)
        scanf("%d", &(mat.dados[mat.numLin - 1][j]));
    return mat;
}

Matriz removeLinha(Matriz mat) {
    /*Lê um inteiro e remove a linha da matriz de índice correspondente (retorna a matriz modificada)*/
    int indexRemov, *aux; //indexRemov - índice da linha a ser removida
    scanf("%d", &indexRemov);
    aux = mat.dados[indexRemov];
    for (int i = indexRemov; i < mat.linAloc - 1; i++)
        mat.dados[i] = mat.dados[i + 1]; //move cada linha abaixo da removida para cima
    mat.dados[mat.linAloc - 1] = aux; //move a linha removida para a última posição alocada
    mat.numLin--;
    if (mat.numLin <= mat.linAloc / 4)
        mat = realocaLinha(mat, '-');
    return mat;
}

void insercaoOrdenada(int *vetor, int len, int valor) {
    /*Dado um vetor ordenado e seu tamanho (len), insere o valor mantendo a ordem*/
    int i;
    for (i = len - 1; i >= 0 && vetor[i] > valor; i--)
        vetor[i + 1] = vetor[i]; //move elementos para a direita até achar a posição de inserção
    vetor[i + 1] = valor;
}

Matriz insereColuna(Matriz mat) {
    /*Lê e insere um elemento a cada linha da matriz mantendo-as em ordem crescente (retorna a matriz modificada)*/
    int elem; //elemento a ser inserido
    if (mat.numCol + 1 > mat.colAloc)
        mat = realocaColuna(mat, '+');
    for (int i = 0; i < mat.numLin; i++) {
        scanf("%d", &elem);
        insercaoOrdenada(mat.dados[i], mat.numCol, elem);
    }
    mat.numCol++;
    return mat;
}

Matriz removeColuna(Matriz mat) {
    /*Lê um inteiro e remove a coluna da matriz de índice correspondente (retorna a matriz modificada)*/
    int indexRemov; //índice da coluna a ser removida
    scanf("%d", &indexRemov);
    for (int i = 0; i < mat.numLin; i++) {
        for (int j = indexRemov; j < mat.numCol - 1; j++)
            mat.dados[i][j] = mat.dados[i][j + 1];
            //move os elementos à direita de indexRemov uma unidade para a esquerda
    mat.numCol--;
    if (mat.numCol <= mat.colAloc / 4)
        mat = realocaColuna(mat, '-');
    return mat;
}