#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pilha.h"

#define MAX 500

int extrai_numero(char *str) {
    /*Dada uma string com apenas um número, retorna esse número*/
    int num = 0; //num: número na string
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= '0' && str[i] <= '9')
            num = (num * 10) + str[i] - '0'; //multiplica por 10 e adiciona n° a cada laço
    return num;
}

int main() {
    p_pilha pilha = criar_pilha();
    p_fila fila = criar_fila(MAX);
    char *str = malloc(MAX * sizeof(char)); //vetor para guardar cada entrada
    int qtde; //quantidade de caracteres empilhados/deletados com EXEC/DEL
    fgets(str, MAX, stdin);
    while (strcmp("EXIT", str)) { //enquanto str != "EXIT" 
        str[strcspn(str, "\n")] = '\0'; //remoção do '\n' no final do vetor
        if (strstr(str, "EXEC") != NULL) { //função retorna != NULL se "EXEC" for substring de str
            qtde = extrai_numero(str);
            for (int i = 0; i < qtde; i++)
                empilha(pilha, desenfileira(fila));
        } else if (strstr(str, "DEL") != NULL) {
            qtde = extrai_numero(str);
            for (int i = 0; i < qtde; i++)
                desempilha(pilha);
        } else { //passagem de string a ser enfileirada
            enfileira(fila, str);
        }
        printf("FILA ATUAL: ");
        print_fila(fila);
        printf("\nPILHA ATUAL: ");
        print_pilha(pilha);
        printf("\n####\n");
        fgets(str, MAX, stdin);
    }
    destruir_pilha(pilha);
    destruir_fila(fila);
    free(str);
}