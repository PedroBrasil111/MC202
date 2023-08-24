#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAI(i) ((i - 1) / 2)  //pai do item na posição i no heap
#define F_ESQ(i) (2 * i + 1)  //filho esquerdo do item em i
#define F_DIR(i) (2 * i + 2)  //filho direito do item em i

struct Par {  //item do heap, representando um par (p, c)
    //menor c, maior prioridade -- desempate: maior p, maior prioridade
    int p, c;
};

typedef struct Fila_prio *p_fp;  //ponteiro para fila prioritária

struct Fila_prio {   //heap de pares (p, c)
    struct Par *v;   //v: vetor do heap
    int len, tam;    //len: tamanho ocupado, tam: tamanho alocado
};

/* Cria um par, dados seus valores de p e c */
struct Par criar_par(int p, int c) {
    struct Par item;
    item.c = c;
    item.p = p;
    return item;
}

/* Troca dois pares de lugar */
void troca(struct Par *a, struct Par *b) {
    struct Par aux = *a;
    *a = *b;
    *b = aux;
}

/* Compara a prioridade de dois pares. Retorna 1 se par1 > par2, e -1 se par1 < par2 */
int compara_prioridade(struct Par par1, struct Par par2) {
    if (par1.c < par2.c || (par1.c == par2.c && par1.p > par2.p))
        return 1; //prioridade de par1 é maior que de par2
    return -1; //par1 < par2
}

/* Cria um heap com espaço total alocado igual a tam */
p_fp criar_filaprio(int tam) {
    p_fp fprio = malloc(tam * sizeof(struct Fila_prio));
    fprio->v = malloc(tam * sizeof(struct Par));
    fprio->tam = tam;
    fprio->len = 0;
    return fprio;
}

/* Sobe um item inicialmente na posição pos do heap se necessário */
void sobe_no_heap(p_fp fprio, int pos) {
    if (pos > 0 && compara_prioridade(fprio->v[pos], fprio->v[PAI(pos)]) > 0) {
        //prioridade do pai é menor -- troca os pares e segue subindo
        troca(&fprio->v[PAI(pos)], &fprio->v[pos]);
        sobe_no_heap(fprio, PAI(pos));
    }
}

/* Insere um par no heap */
void insere(p_fp fprio, struct Par par) {
    fprio->v[fprio->len] = par; //insere na última posição
    fprio->len++;
    sobe_no_heap(fprio, fprio->len - 1); //sobe arrumando o heap
}

/* Desce um item inicialmente na posição pos do heap se necessário */
void desce_no_heap(p_fp fprio, int pos) {
    int maior_filho; //guarda a posição do filho de maior prioridade de pos
    if (F_ESQ(pos) < fprio->len) {
            maior_filho = F_ESQ(pos); //assume inicialmente que F_ESQ é o maior
        if (F_DIR(pos) < fprio->len &&
            compara_prioridade(fprio->v[F_DIR(pos)], fprio->v[F_ESQ(pos)]) > 0)
            //F_DIR tem mais prioridade que F_ESQ
            maior_filho = F_DIR(pos);
        if (compara_prioridade(fprio->v[maior_filho], fprio->v[pos]) > 0) {
            //prioridade do maior filho é maior que de pos -- troca e segue descendo
            troca(&fprio->v[maior_filho], &fprio->v[pos]);
            desce_no_heap(fprio, maior_filho);
        }
    }
}

/* Retorna o valor de p do par de maior prioridade e o remove do heap */
int remover(p_fp fprio) {
    int p = fprio->v[0].p;  //v[0] sempre tem maior prioridade
    troca(&fprio->v[0], &fprio->v[fprio->len - 1]); //troca último com primeiro
    fprio->len--; //"remove" o par de maior prioridade
    desce_no_heap(fprio, 0); //ajeita o heap
    return p;
}

/* Retorna a posição do par com o valor de p dado, e -1 se não o encontrar */
int busca(p_fp fprio, int p) {
    for (int i = 0; i < fprio->len; i++)
        if (fprio->v[i].p == p)
            return i;
    return -1;
}

/* Muda o valor de c do par na posição pos do vetor */
void muda_prioridade(p_fp fprio, int pos, int c) {
    if (fprio->v[pos].c > c) { //c diminui -> prioridade aumenta
        fprio->v[pos].c = c;
        sobe_no_heap(fprio, pos); //sobe arrumando
    } else { //c aumenta -> prioridade diminui
        fprio->v[pos].c = c;
        desce_no_heap(fprio, pos); //desce arrumando
    }
}

/* Libera o heap */
void liberar(p_fp fprio) {
    free(fprio->v);
    free(fprio);
}

int main() {
    int tam, numOp, p, c, numRemov;
    //tam: número de pares (p, c), numOp: qtde de operações realizadas
    //numRemov: número de processos removidos quando usado o comando R
    p_fp fprio;
    char comando; //comando que deve ser realizado ('R' ou 'M')
    scanf("%d", &tam);
    fprio = criar_filaprio(tam);
    for (int i = 0; i < tam; i++) {
        scanf("%d %d ", &p, &c);
        insere(fprio, criar_par(p, c));
    }
    scanf("%d", &numOp);
    for (int i = 0; i < numOp; i++) {
        scanf(" %c", &comando);
        if (comando == 'R') { //remoção
            scanf("%d", &numRemov);
            printf("PROCESSOS REMOVIDOS:");
            for (int i = 0; i < numRemov; i++)
                printf(" %d", remover(fprio));
            printf("\n");
        } else if (comando == 'M') { //modificação da prioridade
            scanf("%d %d", &p, &c);
            //busca o par com o valor dado de p e altera c
            muda_prioridade(fprio, busca(fprio, p), c);
        }
    }
    printf("FINALIZADO!\n");
    liberar(fprio);
}