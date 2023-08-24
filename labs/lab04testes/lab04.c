#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n, *sold;
    // n = qtde soldados, sold = vetor contendo as experiências dos soldados
} tropaForte;

int *leTropa(int lenTropa) {
    /* Aloca, lê e retorna um vetor com as experiências de uma tropa de tamanho lenTropa. */
    int *tropa;
    tropa = malloc(lenTropa * sizeof(int));
    for (int i = 0; i < lenTropa; i++) {
        scanf("%d", &tropa[i]);
    }
    return tropa;
}

tropaForte criaForte(int *tropa, int lenTropa) {
    /* Dada uma tropa, gera e retorna a sub-tropa forte. */
    tropaForte forte;
    int i, soma, maiorSoma = -101, ini, fim;
    /* soma, maiorSoma - usadas para calcular a maior soma sequencial de experiências na tropa;
       inicialização maiorSoma = -101 pois a menor exp. possível é -100;
       ini/fim - guardam os índices iniciais/finais da sub-tropa forte da tropa */
    for (i = 0; i < lenTropa; i++) {
        soma = 0;
        for (int j = 0; j < (lenTropa - i); j++) {
            //soma de tropa[i] até tropa[j], para cada i fixado e j >= i variando
            soma += tropa[i + j];
            if (soma > maiorSoma) {
                maiorSoma = soma;
                ini = i;
                fim = i + j;
            }
        }
    }
    forte.n = fim - ini + 1; //tamanho da sub-tropa forte
    forte.sold = malloc(forte.n * sizeof(int));
    for (i = 0; i < forte.n; i++)
        forte.sold[i] = tropa[ini + i];
    return forte;
}

void printForte(tropaForte t, int numTropa) {
    /* Imprime uma tropa forte.
       Na função main, um contador será utilizado como numTropa (num. da tropa atual). */
    printf("Sub-tropa Forte %d: ", numTropa + 1);
    for (int i = 0; i < t.n; i++) {
        printf("%d ", t.sold[i]);
    }
    printf("\n");
}

void subTropaElite(int *elite, int lenElite, int media) {
    /* Dada a tropa de elite, seu tamanho (lenElite) e a média das exp.,
       cria e imprime a sub-tropa de elite. */
    tropaForte subElite; // = sub-tropa de elite
    for (int i = 0; i < lenElite; i++) {
        elite[i] -= media; // normaliza a tropa de elite
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

void TropaElite(tropaForte *fortes, int numTropas) {
    /* Dado um vetor das tropas fortes (*fortes) e o número de tropas (numTropas),
       cria a tropa forte (junção das tropas fortes) para gerar a sub-tropa de elite */
    int i, j = 0, lenElite = 0, soma = 0, *elite;
    // j - contador para criar a tropa de elite (*elite) de tamanho lenElite
    for (i = 0; i < numTropas; i++) {
        lenElite += fortes[i].n;
    }
    elite = malloc(lenElite * sizeof(int));
    for (i = 0; i < numTropas; i++) {
        for (int k = 0; k < fortes[i].n; k++) {
            // i itera sobre fortes, k itera sobre fortes[i].sold para criar elite
            elite[j] = fortes[i].sold[k];
            soma += elite[j];
            j++;
        }
    }
    subTropaElite(elite, lenElite, soma/lenElite);
}

int main() {
    int i, numTropas, lenTropa, *tropa;
    /* numTropas = qtde de tropas, tropa = vetor com as experiências.
       lenTropa = tamanho da tropa. lenTropa e tropa serão atualizados a cada tropa lida. */
    tropaForte *fortes; //vetor com todas as tropas fortes
    scanf("%d", &numTropas);
    fortes = malloc(numTropas * sizeof(tropaForte));
    for (i = 0; i < numTropas; i++) {
        scanf("%d", &lenTropa);
        tropa = leTropa(lenTropa);
        fortes[i] = criaForte(tropa, lenTropa);
        printForte(fortes[i], i);
        free(tropa);
    }
    TropaElite(fortes, numTropas);
    for (i = 0; i < numTropas; i++) {
        free(fortes[i].sold);
    }
    free(fortes);
    return 0;
}