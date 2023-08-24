#include <stdio.h>
#include <string.h>

#define MAX 99

void copiaMat(int mat1[][MAX], int mat2[][MAX], int len) {
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            mat2[i][j] = mat1[i][j];
}

void criaMat(int A[][MAX], int B[][MAX], int len) {
    int cor = 1, j = 0;
    do {
        for (int i = 0; i < len; i++) {
            A[i][j] = cor;
            B[i][j] = cor;
        }
        j++;
        if (j % 3 == 0)
            cor = (cor + 1) % 2; //Troca de cor a cada 3 colunas
    } while (j < len);
}

void printMat(int mat[][MAX], int len) {
    for (int i = 0; i < len; i++) {
        printf("\n");
        for (int j = 0; j < len; j++)
            printf("%d ", mat[i][j]);
    }
    printf("\n");
}

void transposta(int a[][MAX], int b[][MAX], int len) {  
    char mat1, mat2;
    int z[MAX][MAX];
    scanf("%c %c", &mat1, &mat2);
    if (mat1 == 'A') {
        for (int j = 0; j < len; j++)
            for (int i = len - 1; i >= 0; i--)
                z[j][len - 1 - i] = a[i][j];
    } else {
        for (int j = 0; j < len; j++)
            for (int i = len - 1; i >= 0; i--)
                z[j][len - 1 - i] = b[i][j];
    }
    if (mat2 == 'A') {
        copiaMat(z, a, len);
        printMat(a, len);
    } else {
        copiaMat(z, b, len);
        printMat(b, len);
    }
}

void soma(int a[][MAX], int b[][MAX], int len) {
    char mat1, mat2, mat3;
    int z[MAX][MAX];
    scanf("%c %c %c", &mat1, &mat2, &mat3);
    if (mat1 != mat2) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                z[i][j] = a[i][j] + b[i][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    } else if (mat1 == 'B') { //mat1 = mat2 = 'B'
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                z[i][j] = 2 * b[i][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    } else { //mat1 = mat2 = 'A'
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                z[i][j] = 2 * a[i][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    }
    if (mat3 == 'A') {
        copiaMat(z, a, len);
        printMat(a, len);
    } else {
        copiaMat(z, b, len);
        printMat(b, len);
    }
}

void multiElem(int a[][MAX], int b[][MAX], int len) {
    char mat1, mat2, mat3;
    int z[MAX][MAX];
    scanf("%c %c %c", &mat1, &mat2, &mat3);
        if (mat1 != mat2) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                z[i][j] = a[i][j] * b[i][j];
            }
        }
    } else if (mat1 == 'B') { //mat1 = mat2 = 'B'
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                z[i][j] = b[i][j] * b[i][j];
            }
        }
    } else { //mat1 = mat2 = 'A'
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                z[i][j] = a[i][j] * a[i][j];
            }
        }
    }
    if (mat3 == 'A') {
        copiaMat(z, a, len);
        printMat(a, len);
    } else {
        copiaMat(z, b, len);
        printMat(b, len);
    }
}

void multiMat(int a[][MAX], int b[][MAX], int len) {
    char mat1, mat2, mat3;
    int z[MAX][MAX];
    scanf("%c %c %c", &mat1, &mat2, &mat3);
    if (mat1 != mat2) {
    for (int i = 0; i < len; i ++)
        for (int j = 0; j < len; j++) {
            z[i][j] = 0;
            for (int k = 0; k < len; k++) {
                z[i][j] += a[i][k] * b[k][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    } else if (mat1 == 'A') {
    for (int i = 0; i < len; i ++)
        for (int j = 0; j < len; j++) {
            z[i][j] = 0;
            for (int k = 0; k < len; k++) {
                z[i][j] += a[i][k] * a[k][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    } else {
    for (int i = 0; i < len; i ++)
        for (int j = 0; j < len; j++) {
            z[i][j] = 0;
            for (int k = 0; k < len; k++) {
                z[i][j] += b[i][k] * b[k][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    }
    if (mat3 == 'A') {
        copiaMat(z, a, len);
        printMat(a, len);
    } else {
        copiaMat(z, b, len);
        printMat(b, len);
    }
}

void borda(int a[][MAX], int b[][MAX], int len) {
    int z[MAX][MAX], temBorda; //temBorda: condição
    char mat1, mat2;
    scanf("%c %c", &mat1, &mat2);
    if (mat1 == 'A') {
        copiaMat(a, z, len);
        for (int i = 0; i < len - 2; i++)
            for (int j = 0; j < len - 2; j++) {
                temBorda = 1;
                for (int k = 0; k < 3 && temBorda; k++) // Checa se a submatriz 3x3 é composta apenas por 1's
                    for (int l = 0; l < 3 && temBorda; l++)
                        if (a[i+k][j+l] == 0) 
                            temBorda = 0;
                if (temBorda)
                    z[i + 1][j + 1] = 0;
            }
    } else {
        copiaMat(a, z, len);
        for (int i = 0; i < len - 2; i++)
            for (int j = 0; j < len - 2; j++) {
                temBorda = 1;
                for (int k = 0; k < 3 && temBorda; k++) // Checa se a submatriz 3x3 é composta apenas por 1's
                    for (int l = 0; l < 3 && temBorda; l++)
                        if (b[i+k][j+l] == 0) 
                            temBorda = 0;
                if (temBorda)
                    z[i + 1][j + 1] = 0;
            }
    }
    if (mat2 == 'A') {
        copiaMat(z, a, len);
        printMat(a, len);
    } else {
        copiaMat(z, b, len);
        printMat(b, len);
    }
}

int main() {
    char operacao[MAX];
    int len, o, a[MAX][MAX], b[MAX][MAX];
    scanf("%d %d", &len, &o);
    criaMat(a, b, len);
    for (int i = 0; i < o; i++) {
        scanf("%s ", operacao);
        if (! strcmp(operacao, "TRANSPOSTA")) {
            transposta(a, b, len);
        } else if (! strcmp(operacao, "SOMA")) {
            soma(a, b, len);
        } else if (! strcmp(operacao, "MULTI_ELEM")) {
            multiElem(a, b, len);
        } else if (! strcmp(operacao, "MULTI_MAT")) {
            multiMat(a, b, len);
        } else {
            borda(a, b, len);
        }
    }
}