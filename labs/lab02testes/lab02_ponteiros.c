#include <stdio.h>
#include <string.h>

#define MAX 99

typedef struct {
    int m[MAX][MAX], n; //matriz m quadrada nxn
} matriz;

void printMat(matriz mat) {
    for (int i = 0; i < mat.n; i++) {
        printf("\n");
        for (int j = 0; j < mat.n; j++)
            printf("%d ", mat.m[i][j]);
    }
    printf("\n");
}

matriz criaMat(int n) {
    matriz mat;
    int cor = 1, j = 0;
    mat.n = n;
    do {
        for (int i = 0; i < mat.n; i++) 
            mat.m[i][j] = cor;
        j++;
        if (j % 3 == 0)
            cor = (cor + 1) % 2; //Troca de cor a cada 3 colunas
    } while (j < mat.n);
    return mat;
}

matriz transposta(matriz mat) {
    matriz aux;
    aux.n = mat.n;
    for (int j = 0; j < mat.n; j++)
        for (int i = mat.n - 1; i >= 0; i--)
            aux.m[j][mat.n - 1 - i] = mat.m[i][j];
    return aux;
}

matriz soma(matriz mat1, matriz mat2) {
    matriz aux;
    aux.n = mat1.n;
    for (int i = 0; i < mat1.n; i++)
        for (int j = 0; j < mat1.n; j++) {
            aux.m[i][j] = mat1.m[i][j] + mat2.m[i][j];
            if (aux.m[i][j] > 1)
                aux.m[i][j] = 1;
        }
    return aux;
}

matriz multiElem(matriz mat1, matriz mat2) {
    matriz aux;
    aux.n = mat1.n;
    for (int i = 0; i < mat1.n; i++)
        for (int j = 0; j < mat1.n; j++)
            aux.m[i][j] = mat1.m[i][j] * mat2.m[i][j];
    return aux;
}

matriz multiMat(matriz mat1, matriz mat2) {
    matriz aux;
    aux.n = mat1.n;
    for (int i = 0; i < mat1.n; i++)
        for (int j = 0; j < mat1.n; j++) {
            aux.m[i][j] = 0;
            for (int k = 0; k < mat1.n; k++)
                aux.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
            if (aux.m[i][j] > 1)
                aux.m[i][j] = 1;
        }
    return aux;
}

matriz borda(matriz mat) {
    matriz aux = mat;
    int temBorda;
    for (int i = 0; i < mat.n - 2; i++)
        for (int j = 0; j < mat.n - 2; j++) {
            temBorda = 1;
            for (int k = 0; k < 3 && temBorda; k++) // Checa se a submatriz 3x3 é composta apenas por 1's
                for (int l = 0; l < 3 && temBorda; l++)
                    if (mat.m[i+k][j+l] == 0) 
                        temBorda = 0;
            if (temBorda)
                aux.m[i + 1][j + 1] = 0;
    }
    return aux;
}

int main() {
    char operacao[MAX], mat1, mat2, mat3;
    matriz *p1, *p2, *p3;
    int i, n, o; //n: dimensões, o: n° operações
    matriz a, b;
    scanf("%d", &n);
    a = b = criaMat(n);
    scanf("%d", &o);
    for (i = 0; i < o; i++) {
        scanf(" %s", operacao);
        scanf(" %c %c", &mat1, &mat2);
        if (mat1 == 'A')
            p1 = &a;
        else
            p1 = &b;
        if (mat2 == 'A')
            p2 = &a;
        else
            p2 = &b;
        if (strcmp(operacao, "TRANSPOSTA") == 0) {
            *p2 = transposta(*p1);
            printMat(*p2);
        } else if (strcmp(operacao, "BORDAS") == 0) {
            *p2 = borda(*p1);
            printMat(*p2);
        } else {
            scanf(" %c", &mat3);
            if (mat3 == 'A')
                p3 = &a;
            else
                p3 = &b;
            if (strcmp(operacao, "SOMA") == 0) {
                *p3 = soma(*p1, *p2);
            } else if (strcmp(operacao, "MULTI_ELEM") == 0) {
                *p3 = multiElem(*p1, *p2);
            } else {
                *p3 = multiMat(*p1, *p2);
            }
            printMat(*p3);
        }
    }
    return 0;
}