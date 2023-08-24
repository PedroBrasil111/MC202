typedef struct {
    int **dados, numCol, numLin, colAloc, linAloc;
    /*dados - a matriz em si;
      numCol/numLin - número de linhas/colunas ocupadas (sendo utilizadas);
      colAloc/linAloc - número de linhas/colunas alocadas (sendo utilizadas ou não).*/
} Matriz;

Matriz leMatriz();
//Lê o número de linhas, de colunas e elementos (em ordem crescente) para criar a matriz e retorná-la

void destroiMatriz(Matriz mat);
//Libera a matriz

void printMatriz(Matriz mat);
//Imprime a matriz

Matriz insereLinha(Matriz mat);
//Lê e insere uma linha (em ordem crescente) no final da matriz (retorna a matriz modificada)

Matriz removeLinha(Matriz mat);
//Lê um inteiro e remove a linha da matriz de índice correspondente (retorna a matriz modificada)

Matriz insereColuna(Matriz mat);
//Lê e insere um elemento a cada linha da matriz mantendo-as em ordem crescente (retorna a matriz modificada)

Matriz removeColuna(Matriz mat);
//Lê um inteiro e remove a coluna da matriz de índice correspondente (retorna a matriz modificada)