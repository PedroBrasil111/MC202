#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1783
#define MAX_NOME 100

typedef struct Processo *p_proc;

typedef struct Processo {
    int id;
    int tempo;
    char nome_proc[MAX_NOME];
} Processo;

typedef struct hash *p_hash;

struct hash {
    p_proc vetor[MAX];
};

int hash(int chave) {
    char chave_string[MAX_NOME];
    int i, n = 0;
    sprintf(chave_string, "%d", chave); // guarda a chave em forma de string em chave_string
    for (i = 0; i < strlen(chave_string); i++)
        n = (256 * n + chave_string[i]) % MAX;
    return n;
}

p_proc cria_processo(int id, int tempo, char nome_proc[]) {
    p_proc p = malloc(sizeof(Processo));
    p->id = id;
    p->tempo = tempo;
    strcpy(p->nome_proc, nome_proc);
    return p;
}

void destroi_processo(p_proc p) {
    free(p);
}

p_hash cria_hash() {
    int i;
    p_hash t = malloc(sizeof(struct hash));
    for (i = 0; i < MAX; i++)
        t->vetor[i] = NULL;
    return t;
}

p_proc inserir_lista(p_proc lista, int id, int tempo, char nome_proc[]) {
    p_proc p = cria_processo(id, tempo, nome_proc);
    return p;
}

int pode_inserir(p_hash t, int n) {
    if (t->vetor[n] == NULL || strcmp(t->vetor[n]->nome_proc, "r") == 0)
        return 1;
    return 0;
}

void inserir(p_hash t, int chave, int tempo, char nome_proc[]) {
    int i, n = hash(chave);
    for (i = n; ; i = (i + 1) % MAX) { // sem condição porque é certeza que dá pra inserir
        if (pode_inserir(t, i)) {
            if (t->vetor[i] != NULL)
                destroi_processo(t->vetor[i]);
            t->vetor[i] = inserir_lista(t->vetor[i], chave, tempo, nome_proc);
            printf("PROCESSO %d INSERIDO!\n", chave);
            break;
        }
    }
}

int encontrou_processo(p_hash t, int n, int chave) {
    if (t->vetor[n] != NULL && t->vetor[n]->id == chave && strcmp(t->vetor[n]->nome_proc, "r") != 0)
        return 1;
    return 0;
}

void remover(p_hash t, int chave) {
    int i, n = hash(chave);
    for (i = n; ; i = (i + 1) % MAX) {
        if (encontrou_processo(t, i, chave)) {
            t->vetor[i]->nome_proc[0] = 'r'; // removido
            t->vetor[i]->nome_proc[1] = '\0';
            printf("PROCESSO %d REMOVIDO!\n", chave);
            break;
        }
    }
}

void consulta_nome(p_hash t, int chave) {
    int i, n = hash(chave), voltas = 0, encontrou = 0;
    for (i = n; voltas != 2; i = (i + 1) % MAX) {
        if (i == n)
            voltas++;
        if (encontrou_processo(t, i, chave)) {
            printf("PROCESSO %d: %s\n", chave, t->vetor[i]->nome_proc);
            encontrou = 1;
            break;
        }
    }
    if (! encontrou)
        printf("PROCESSO %d NAO ENCONTRADO!\n", chave);
}

void consulta_tempo(p_hash t, int chave) {
    int i, n = hash(chave);
    for (i = n; ; i = (i + 1) % MAX) {
        if (encontrou_processo(t, i, chave)) {
            printf("TEMPO DO PROCESSO %d: %d DIAS.\n", chave, t->vetor[i]->tempo);
            break;
        }
    }
}

void destroi_hash(p_hash t) {
    int i;
    for (i = 0; i < MAX; i++) {
        if (t->vetor[i] != NULL)
            destroi_processo(t->vetor[i]);
    }
    free(t);
}

int main() {
    int i, N, id, tempo;
    p_hash t = cria_hash();
    char operacao, nome_proc[MAX_NOME];
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf(" %c ", &operacao);
        scanf("%d", &id);
        if (operacao == 'I') {
            scanf(" %s ", nome_proc);
            scanf("%d", &tempo);
            inserir(t, id, tempo, nome_proc);
        } else if (operacao == 'R') {
            remover(t, id);
        } else if (operacao == 'C') {
            consulta_nome(t, id);
        } else  {
            consulta_tempo(t, id);
        }
    }
    destroi_hash(t);
    printf("FINALIZADO!");
}