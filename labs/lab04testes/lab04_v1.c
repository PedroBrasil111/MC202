#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n, *sold;
    //n = qtde soldados, sold = vetor contendo as experiências dos soldados
} tropaForte;

int *criaTropa(int n) {
    int *tropa;
    tropa = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &tropa[i]);
    }
    return tropa;
}

tropaForte criaForte(int *tropa, int lenTropa) {
    tropaForte t;
    int soma, maiorSoma = -101, ini, fim;
    //ini/fim guardam os index iniciais/finais da sub-tropa forte de uma tropa
    for (int i = 0; i < lenTropa; i++) {
        soma = 0;
        for (int j = 0; j < (lenTropa - i); j++) {
            soma += tropa[i + j];
            if (soma > maiorSoma) {
                maiorSoma = soma;
                ini = i;
                fim = i + j;
            }
        }
    }
    t.n = fim - ini + 1;
    t.sold = malloc(t.n * sizeof(int));
    for (int i = 0; i < t.n; i++)
        t.sold[i] = tropa[ini + i];
    return t;
}

void printForte(tropaForte t, int numTropa) {
    printf("Sub-tropa Forte %d: ", numTropa + 1);
    for (int i = 0; i < t.n; i++) {
        printf("%d ", t.sold[i]);
    }
    printf("\n");
}

void subTropaElite(tropaForte *fortes, int numTropas) {
    int lenElite = 0, soma = 0, j = 0, media, *elite;
    tropaForte subElite;
    for (int i = 0; i < numTropas; i++) {
        lenElite += fortes[i].n;
    }
    elite = malloc(lenElite * sizeof(int));
    for (int i = 0; i < numTropas; i++) {
        for (int k = 0; k < fortes[i].n; k++) {
            elite[j] = fortes[i].sold[k];
            soma += elite[j];
            j++;
        }
    }
    media = soma / lenElite;
    for (int i = 0; i < lenElite; i++) {
        elite[i] -= media;
    }
    subElite = criaForte(elite, lenElite);
    printf("Sub-tropa Elite: ");
    for (int i = 0; i < subElite.n; i++) {
        printf("%d ", subElite.sold[i] + media);
    }
    printf("\n");
    free(elite);
    free(subElite.sold);
}

int main() {
    int numTropas, lenTropa, *tropa;
    tropaForte *fortes;
    scanf("%d", &numTropas);
    fortes = malloc(numTropas * sizeof(tropaForte));
    for (int i = 0; i < numTropas; i++) {
        scanf("%d", &lenTropa);
        tropa = criaTropa(lenTropa);
        fortes[i] = criaForte(tropa, lenTropa);
        printForte(fortes[i], i);
        free(tropa);
    }
    subTropaElite(fortes, numTropas);
    for (int i = 0; i < numTropas; i++) {
        free(fortes[i].sold);
    }
    free(fortes);
    return 0;
}