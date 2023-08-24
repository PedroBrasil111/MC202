/* Ponteiro para Processo */
typedef struct Processo *p_processo;

/* Processo com id, tempo e nome */
struct Processo {
    int id, tempo, removido;
    //removido == 1: processo foi removido do hash, == 0: caso contrário
    char *nome;
};

/* Ponteiro para Hash */
typedef struct Hash *p_hash;

/* Implementação de hash com endereçamento aberto */
struct Hash {
    p_processo *v_proc;
    int tam;
    //vetor de processos v_proc de tamanho igual a tam
};

/* Cria o processo com id, tempo e nome dados, retorna o ponteiro */
p_processo criar_processo(int id, int tempo, char *nome);

/* Cria a estrutura do hash com tamanho "tam" */
p_hash criar_hash(int tam);

/* Insere o processo no hash (assumindo que há espaço disponível) */
void inserir(p_hash h, p_processo proc);

/* Dado um id (no hash), remove o processo correspondente */
void remover(p_hash h, int id);

/* Dado um id, retorna o nome do processo se ele estiver no hash, NULL se não estiver */
char *consultar_nome(p_hash h, int id);

/* Dado um id (no hash), retorna o tempo do processo */
int consultar_tempo(p_hash h, int id);

/* Libera o hash */
void liberar_hash(p_hash h); 