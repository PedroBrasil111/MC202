/*
void movCicl(int u[], int lenU) {
	int P, aux;
	scanf("%d", &P); //P = passo
	for (int i = 0; i < P; i++) {
    	aux = u[lenU - 1];
    	for (int j = lenU - 2; j >= 0; j--)
    		u[j + 1] = u[j];
    	u[0] = aux;
    }
}
*/

#include <stdio.h>

void lerVetor(int vetor[], int len) {
    for (int i = 0; i < len; i++)
		scanf("%d", &vetor[i]);
}

void printVetor(int vetor[], int len) {
    for (int i = 0; i < len; i++)
    	printf("%d ", vetor[i]);
    printf("\n");
}

void opBanner(int u[], int lenU) {       //Operação c/ conjunto de Banner
    int taNoConj, B, conjBanner[1000];   //taNoConj: condição
    scanf("%d", &B);                     //B = len(conjBanner)
    lerVetor(conjBanner, B);
    for (int i = 0; i < lenU; i++) {
        taNoConj = 0;
        for (int j = 0; j < B && ! taNoConj; j ++)
            if (u[i] == conjBanner[j])
            	taNoConj = 1;
        if (! taNoConj)
            u[i] = 0;
    }
}

void mobius(int u[], int lenU) { //Multip. de Mobius
    int m;
    scanf("%d", &m);
    for (int i = 1; i < lenU; i += 2)
        u[i] *= m;
}

void movCicl(int u[], int lenU) { //Movimento cíclico
    int p, ciclado[lenU];
    scanf("%d", &p); //p = passo
    for (int i = 0; i < lenU; i++) 
        ciclado[(i + p) % lenU] = u[i];
    for (int i = 0; i < lenU; i++)
        u[i] = ciclado[i];
}

void inverterVetor(int u[], int lenU) { //Inversão
    int aux;
    for (int i = 0; i < lenU / 2; i++) {
        aux = u[i];
        u[i] = u[lenU - 1 - i];
        u[lenU - 1 - i] = aux;
    }
}

int main() {
    int t, u[1000], numOp, op;	//op: operação
    scanf("%d", &t);            //t = len(u)
    lerVetor(u, t);
    scanf("%d", &numOp);
    for(int i = 0; i < numOp; i++) {
        scanf("%d", &op);
        if (op == 1) {
            opBanner(u, t);
        } else if (op == 2) {
            mobius(u, t);
        } else if (op == 3) {
            movCicl(u, t);
        } else if (op == 4) {
            inverterVetor(u, t);
        }
        printVetor(u, t);
    }
    return 0;
}