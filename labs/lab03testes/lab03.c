#include <stdio.h>
#include "represa.h"

#define MAX 1000

int main() {
    int i, numRepresas;
    Represa represas[MAX];
    scanf("%d", &numRepresas);
    for (i = 0; i < numRepresas; i++)
        represas[i] = leRepresa();
    padronizaNome(represas, numRepresas);
    for (i = 0; i < numRepresas; i++)
        relatorioRepresa(represas[i]);
    return 0;
}