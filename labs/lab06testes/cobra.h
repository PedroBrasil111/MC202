typedef struct no *p_no;

struct no {
    int x, y;       //posição do nó na matriz
    p_no ant, prox; //ponteiros para os nós anterior/próximo da lista
};

typedef struct cobra *p_cobra;

struct cobra {  //Possui ponteiros para o início (cabeca) e o final (cauda) da lista de nós
    p_no cabeca, cauda;
};

p_cobra cria_cobra();
    /*Cria a cobra sem nós*/

void insere_no(p_cobra cobra, int x, int y);
    /*Insere um nó no início (cabeça) da cobra, dados x e y da nova posição*/

void destruir_cobra(p_cobra cobra);
    /*Libera a cobra*/

int **cria_matriz(int numLin, int numCol);
    /*Dados número de linhas e de colunas, cria uma matriz e a retorna*/

void print_matriz(int **mat, int numLin, int numCol);
    /*Imprime a matriz do jogo*/

void destruir_matriz(int **mat, int numLin);
    /*Libera a matriz*/

void insere_fruta(int **mat, int x_fruta, int y_fruta);
    /*Insere a fruta na matriz dada sua posição*/

void movimento(p_cobra cobra, int numLin, int numCol, char comando);
    /*Dados a cobra e o comando de movimento (w, a, s, d), cria a nova cabeça da cobra.
    numLin e numCol são as informações da matriz do jogo*/

int resultado_movimento(p_cobra cobra, int **mat, int numLin, int numCol);
    /*Chamada deve ser feita após o movimento (mudança da posição da cabeça),
    para atualizar a cobra e a matriz do jogo.
    Retorna 0 se o jogo deve continuar, 1 se deve encerrar com vitória,
    e -1 se deve encerrar com derrota*/