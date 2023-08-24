typedef struct no *p_no; //ponteiro para nó

struct no { //nó contendo uma string
    char *str; //string
    int len;   //tamanho da string
    p_no prox; //próximo nó
};

typedef struct pilha *p_pilha; //ponteiro para pilha

struct pilha { //pilha de char* - implementação por lista ligada
    p_no topo; //ponteiro para o nó no topo da pilha
};

p_pilha criar_pilha();
    /*Cria uma pilha vazia*/

void empilha(p_pilha pilha, char c);
    /*Adiciona um char ao fim do vetor no topo da pilha*/

void desempilha(p_pilha pilha);
    /*Remove um char do fim do vetor no topo da pilha*/

void print_pilha(p_pilha pilha);
    /*Imprime a string na pilha*/

void destruir_pilha(p_pilha pilha);
    /*Libera a pilha*/