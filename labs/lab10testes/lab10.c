#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define MAX 100

int main() {
    p_hash h;
    int num_op, id, tempo; //num_op: quantidade de operações
    char op, *consultado, *nome = malloc(MAX * sizeof(char));
    //op: operação, consultado: nome consultado, nome: nome a inserir
    scanf("%d", &num_op);
    h = criar_hash(num_op); //número de inserções <= num_op
    for (int i = 0; i < num_op; i++) {
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