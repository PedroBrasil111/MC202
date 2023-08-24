typedef struct Fila *p_fila; //ponteiro para fila

struct Fila {
    int *v; //fila de inteiros com vetor circular
    int ini, fim, len; //ini/fim: início/fim do vetor, len: espaço alocado
};

/* Cria uma fila vazia de tamanho len */
p_fila criar_fila(int len);

/* Enfileira num na fila*/
void enfileira(p_fila f, int num);

/* Retorna 1 se a fila estiver vazia, 0 caso contrário */
int fila_vazia(p_fila f);

/* Desenfileira um número da fila e o retorna */
int desenfileira(p_fila f);

/* Libera a fila */
void liberar_fila(p_fila f);