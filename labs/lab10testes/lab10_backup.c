#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

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
p_processo criar_processo(int id, int tempo, char *nome) {
    p_processo proc;
    proc = malloc(sizeof(struct Processo));
    proc->id = id;
    proc->tempo = tempo;
    proc->nome = malloc((strlen(nome) + 1) * sizeof(char));
    proc->removido = 0;
    strcpy(proc->nome, nome);
    return proc;
}

/* Libera o processo */
void liberar_processo(p_processo proc) {
    if (proc != NULL) {
        free(proc->nome);
        free(proc);
    }
}

/* Implementação da função de hash pelo método da multiplicação */
int hash(int id, int tam) {
    float x = (sqrt(5.0) - 1.0) / 2.0 * id; //razão áurea * id
    return (int) tam * (x - (int) x); //x - (int) x equivale a x % 1
}

/* Cria a estrutura do hash com tamanho "tam" */
p_hash criar_hash(int tam) {
    p_hash h;
    h = malloc(sizeof(struct Hash));
    h->v_proc = malloc(tam * sizeof(p_processo));
    for (int i = 0; i < tam; i++)
        h->v_proc[i] = NULL; //inicialização com hash vazio
    h->tam = tam;
    return h;
}

/* Insere o processo no hash (assumindo que há espaço disponível) */
void inserir(p_hash h, p_processo proc) {
    int pos = hash(proc->id, h->tam);
    for (int i = pos; 1; i = (i + 1) % h->tam) {   //CONDIÇÂO!!
        //percorre o hash de pos = hash(id) até achar uma posição válida para inserir
        if (h->v_proc[i] == NULL || h->v_proc[i]->removido) {
            //se tiver um processo que foi removido na posição, o libera antes de inserir
            liberar_processo(h->v_proc[i]);
            h->v_proc[i] = proc;
            return;
        }
    }
}

/* Dado um id (no hash), remove o processo correspondente */
void remover(p_hash h, int id) {
    int pos = hash(id, h->tam);
    for (int i = pos; 1; i = (i + 1) % h->tam) {   //CONDIÇÂO!!
        //percorre o hash de pos = hash(id) até achar o id
        if (h->v_proc[i]->id == id) {
            h->v_proc[i]->removido = 1;
            return;
        }
    }
}

/* Dado um id, retorna o nome do processo se ele estiver no hash, NULL se não estiver */
char *consultar_nome(p_hash h, int id) {
    int pos = hash(id, h->tam), aux = 0;
    for (int i = pos; aux < 2; i = (i + 1) % h->tam) {   //CONDIÇÂO!!
        //percorre o hash de pos = hash(id) até achar o id
        if (i == pos)
            aux++;
            //aux == 2 após percorrer "pos" 2 vezes (id não está no hash), encerrando o laço
        if (h->v_proc[i] != NULL && h->v_proc[i]->id == id && ! h->v_proc[i]->removido)
            //encontrou o id e ele não foi removido
            return h->v_proc[i]->nome;
    }
    return NULL;
}

/* Dado um id (no hash), retorna o tempo do processo */
int consultar_tempo(p_hash h, int id) {
    int pos = hash(id, h->tam);
    for (int i = pos; 1; i = (i + 1) % h->tam) {   //CONDIÇÂO!!
        //percorre o hash de pos = hash(id) até achar o id
        if (h->v_proc[i] != NULL && h->v_proc[i]->id == id)
            return h->v_proc[i]->tempo;
    }
}

/* Libera o hash */
void liberar_hash(p_hash h) {
    for (int i = 0; i < h->tam; i++)
        liberar_processo(h->v_proc[i]);
    free(h->v_proc);
    free(h);
}

int main() {
    p_hash h;
    int numOp, id, tempo; //numOp: quantidade de operações
    char op, *consultado, *nome = malloc(MAX * sizeof(char));
    //op: operação, consultado: nome consultado, nome: nome a inserir
    scanf("%d", &numOp);
    h = criar_hash(numOp);
    for (int i = 0; i < numOp; i++) {
        scanf(" %c %d", &op, &id);
        if (op == 'I') {  //inserção
            scanf("%s %d", nome, &tempo);
            inserir(h, criar_processo(id, tempo, nome));
            printf("PROCESSO %d INSERIDO!\n", id);
        } else if (op == 'R') { //remoção
            remover(h, id);
            printf("PROCESSO %d REMOVIDO!\n", id);
        } else if (op == 'C') { //consulta do nome
            consultado = consultar_nome(h, id);
            if (consultado == NULL) {
                printf("PROCESSO %d NAO ENCONTRADO!\n", id);
            } else {
                printf("PROCESSO %d: %s\n", id, consultado);
            }
        } else {  //consulta do tempo
            printf("TEMPO DO PROCESSO %d: %d DIAS.\n", id, consultar_tempo(h, id));
        }
    }
    free(nome);
    liberar_hash(h);
    printf("FINALIZADO!");
    return 0;
}