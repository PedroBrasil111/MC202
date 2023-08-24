typedef struct no *p_no; //ponteiro para nó

struct no {
    int num; //nome/número do nó
    p_no prox; //próximo nó
};

/* Insere um nó na lista, com no->num = num */
p_no inserir_na_lista(p_no lista, int num);

/* Remove o nó com no->num == num da lista */
p_no remover_da_lista(p_no lista, int num);

/* Libera a lista */
void liberar_lista(p_no lista);