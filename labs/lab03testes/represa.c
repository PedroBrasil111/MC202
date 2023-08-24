#include <stdio.h>
#include "represa.h"

/* Retorna a média simples de um vetor de inteiros */
int mediaSimples(int *dados, int len) {
    int soma = 0;
    for (int i = 0; i < len; i++)
        soma += dados[i];
    return soma / len;
}

/* Cria e retorna uma represa após ler suas informações */
Represa leRepresa() {
    Represa r;
    scanf("%s %f %d", r.nome, &r.nivelMax, &r.qtdMedidas);
    for (int i = 0; i < r.qtdMedidas; i++)
        scanf("%d", &r.medidas[i]);
    r.media = mediaSimples(r.medidas, r.qtdMedidas);
    return r;
}

/* Checa se alguma medida da represa está acima dos 90% permitidos;
 * retorna 1 caso verdade, 0 caso contrário */
int checaNivel(Represa r) {
    for (int i = 0; i < r.qtdMedidas; i++)
        if (r.medidas[i] >= 0.9 * r.nivelMax)
            return 1;
    return 0;
}

/* Retorna o tamanho de uma string */
int strLen(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) ;
    return i;
}

/* Retorna quantos caracteres iguais duas strings possuem */
int comparaString(char *str1, char *str2) {
    int i;
    for (i = 0; str1[i] == str2[i] && str1[i] != '\0'; i++) ;
    return i;
}

/* Remove "represa_de_" do início do nome, se necessário */
void removeRepresaDe(char *nome) {
    int i;
    if (comparaString("represa_de_", nome) == 11) {
        for (i = 0; i < strLen(nome) - 11; i++)
            nome[i] = nome[i + 11]; //
        nome[i] = '\0';
    }
}

/* Dada uma letra c maíuscula, retorna a letra minúscula */
char lowercase(char c) {
    return c - 'A' + 'a';
}

/* Altera os caracteres do nome de acordo com o padrão desejado */
void ajustaCaracteres(char *nome) {
    for (int i = 0; i < strLen(nome); i++) {
        if (nome[i] == '_')
            nome[i] = ' ';
        else if (nome[i] >= 'A' && nome[i] <= 'Z')
            nome[i] = lowercase(nome[i]);
        else if (nome[i] >= '0' && nome[i] <= '9') {
            nome[i] = '\0';
            //return;
        }
    }
}

/* Padroniza o nome das represas no vetor r, len - tamanho de r */
void padronizaNome(Represa *r, int len) {
    for (int i = 0; i < len; i++) { //iteração sobre o vetor de represas (r)
        removeRepresaDe(r[i].nome);
        ajustaCaracteres(r[i].nome);
    }
}

/* Imprime as informações da represa */
void relatorioRepresa(Represa r) {
    printf("NOME: %s\nQTD NIVEIS: %d\nMEDIA: %d\n", r.nome, r.qtdMedidas, r.media);
    if (checaNivel(r))
        printf("CAPACIDADE ACIMA DE 90%% DA MAXIMA!\n");
    printf("#####\n");
}