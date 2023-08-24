typedef struct fila *p_fila; //ponteiro para fila

struct fila { //fila de char - implementação por vetor circular
    char *vetor;
    int ini, fim, len, ocup;
    /*ini/fim: início/final do vetor, len: tamanho do vetor,
    ocup: quantidade de posições ocupadas*/
};

p_fila criar_fila(int len);
    /*Cria uma fila de tamanho len*/

void enfileira(p_fila fila, char *str);
    /*Enfileira uma string na fila*/

char desenfileira(p_fila fila);
    /*Desenfileira um char da fila*/

void print_fila(p_fila fila);
    /*Imprime a string na fila*/

void destruir_fila(p_fila fila);
    /*Libera a fila*/