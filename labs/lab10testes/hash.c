#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

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
    int pos = hash(proc->id, h->tam), i;
    i = pos;
    do {
        //percorre o hash de pos = hash(id) até achar o id
        if (h->v_proc[i] == NULL || h->v_proc[i]->removido) {
            liberar_processo(h->v_proc[i]);
            h->v_proc[i] = proc;
            return;
        }
        i = (i + 1) % h->tam;
    } while (i != pos);
    //não insere se não houver espaço
}

/* Dado um id, remove o processo correspondente */
void remover(p_hash h, int id) {
    int pos = hash(id, h->tam), i;
    i = pos;
    do {
        //percorre o hash de pos = hash(id) até achar o id
        if (h->v_proc[i]->id == id) {
            h->v_proc[i]->removido = 1;
            return;
        }
        i = (i + 1) % h->tam;
    } while (i != pos);
}

/* Dado um id, retorna o nome do processo se ele estiver no hash, NULL se não estiver */
char *consultar_nome(p_hash h, int id) {
    int pos = hash(id, h->tam), i;
    i = pos;
    do {
        //percorre o hash de pos = hash(id) até achar o id
        if (h->v_proc[i] != NULL && h->v_proc[i]->id == id && ! h->v_proc[i]->removido) {
            //encontrou o id e ele não foi removido
            return h->v_proc[i]->nome;
        }
        i = (i + 1) % h->tam;
    } while (i != pos); //i == pos se percorrer todo o hash sem encontrar
    return NULL;
}

/* Dado um id, retorna o tempo do processo */
int consultar_tempo(p_hash h, int id) {
    int pos = hash(id, h->tam), i;
    i = pos;
    do {
        //percorre o hash de pos = hash(id) até achar o id
        if (h->v_proc[i] != NULL && h->v_proc[i]->id == id) {
            //encontrou o id e ele não foi removido
            return h->v_proc[i]->tempo;
        }
        i = (i + 1) % h->tam;
    } while (i != pos);
    return -1; //não encontrou -- não é necessário, porque é certeza que o id está no hash
}

/* Libera o hash */
void liberar_hash(p_hash h) {
    for (int i = 0; i < h->tam; i++)
        liberar_processo(h->v_proc[i]);
    free(h->v_proc);
    free(h);
}