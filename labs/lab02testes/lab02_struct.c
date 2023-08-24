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
    printMat(aux);
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
    printMat(aux);
    return aux;
}

matriz multiElem(matriz mat1, matriz mat2) {
    matriz aux;
    aux.n = mat1.n;
    for (int i = 0; i < mat1.n; i++)
        for (int j = 0; j < mat1.n; j++)
            aux.m[i][j] = mat1.m[i][j] * mat2.m[i][j];
    printMat(aux);
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
    printMat(aux);
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
    printMat(aux);
    return aux;
}

int main() {
    char operacao[MAX], mat1, mat2, mat3;
    int i, n, o; //n: dimensões, o: n° operações
    matriz a, b, aux;
    scanf("%d", &n);
    a = b = criaMat(n);
    scanf("%d", &o);
    for (i = 0; i < o; i++) {
        scanf("%s ", operacao);
        if (strcmp(operacao, "TRANSPOSTA") == 0) {
            scanf("%c %c", &mat1, &mat2);
            if (mat1 == 'A')
                aux = transposta(a);
            else
                aux = transposta(b);
            if (mat2 == 'A')
                a = aux;
            else
                b = aux;
        } else if (strcmp(operacao, "SOMA") == 0) {
            scanf("%c %c %c", &mat1, &mat2, &mat3);
            if (mat1 != mat2)
                aux = soma(a, b);
            else if (mat1 == 'A')
                aux = soma(a, a);
            else
                aux = soma(b, b);
            if (mat3 == 'A')
                a = aux;
            else
                b = aux;
        } else if (strcmp(operacao, "MULTI_ELEM") == 0) {
            scanf("%c %c %c", &mat1, &mat2, &mat3);
            if (mat1 != mat2)
                aux = multiElem(a, b);
            else if (mat1 == 'A')
                aux = multiElem(a, a);
            else
                aux = multiElem(b, b);
            if (mat3 == 'A')
                a = aux;
            else
                b = aux;
        } else if (strcmp(operacao, "MULTI_MAT") == 0) {
            scanf("%c %c %c", &mat1, &mat2, &mat3);
            if (mat1 == 'A' && mat1 != mat2)
                aux = multiMat(a, b);
            else if (mat1 == 'B' && mat1 != mat2)
                aux = multiMat(b, a);
            else if (mat1 == 'A')
                aux = multiMat(a, a);
            else
                aux = multiMat(b, b);
            if (mat3 == 'A')
                a = aux;
            else
                b = aux;
        } else {
            scanf("%c %c", &mat1, &mat2);
            if (mat1 == 'A')
                aux = borda(a);
            else
                aux = borda(b);
            if (mat2 == 'A')
                a = aux;
            else
                b = aux;
        }
    }
    return 0;
}