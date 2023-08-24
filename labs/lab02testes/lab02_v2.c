#include <stdio.h>
#include <string.h>

#define MAX 99

void copiaMat(int original[][MAX], int copia[][MAX], int len) {
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            copia[i][j] = original[i][j];
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

void transposta(int x[][MAX], int y[][MAX], int len) {  
    for (int j = 0; j < len; j++)
        for (int i = len - 1; i >= 0; i--)
            y[j][len - 1 - i] = x[i][j];
    printMat(y, len);
}

void soma(int x[][MAX], int y[][MAX], int z[][MAX], int len) {
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++) {
            z[i][j] = x[i][j] + y[i][j];
            if (z[i][j] > 1)
                z[i][j] = 1;
        }
    printMat(z, len);
}

void multiElem(int x[][MAX], int y[][MAX], int z[][MAX], int len) {
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            z[i][j] = x[i][j] * y[i][j];
    printMat(z, len);
}

void multiMat(int x[][MAX], int y[][MAX], int z[][MAX], int len) {
    for (int i = 0; i < len; i ++)
        for (int j = 0; j < len; j++) {
            z[i][j] = 0;
            for (int k = 0; k < len; k++) {
                z[i][j] += x[i][k] * y[k][j];
                if (z[i][j] > 1)
                    z[i][j] = 1;
            }
        }
    printMat(z, len);
}

void borda(int x[][MAX], int y[][MAX], int len) {
    int temBorda, aux[MAX][MAX];
    copiaMat(x, aux, len);
    for (int i = 0; i < len - 2; i++)
        for (int j = 0; j < len - 2; j++) {
            temBorda = 1;
            for (int k = 0; k < 3 && temBorda; k++) // Checa se a submatriz 3x3 é composta apenas por 1's
                for (int l = 0; l < 3 && temBorda; l++)
                    if (x[i+k][j+l] == 0) 
                        temBorda = 0;
            if (temBorda)
                aux[i + 1][j + 1] = 0;
        }
    copiaMat(aux, y, len);
    printMat(y, len);
}

int main() {
    char operacao[MAX], mat1, mat2, mat3;
    int len, o, a[MAX][MAX], b[MAX][MAX];
    scanf("%d %d", &len, &o);
    criaMat(a, b, len);
    for (int i = 0; i < o; i++) {
        scanf(" %s %c %c", operacao, &mat1, &mat2);

        if (strcmp(operacao, "TRANSPOSTA") == 0) {
            if (mat1 == 'A' && mat1 != mat2)
                transposta(a, b, len);
            else if (mat1 == 'B' && mat1 != mat2)
                transposta(b, a, len);
            else if (mat1 == 'A')
                transposta(a, a, len);
            else
                transposta(b, b, len);
        
        } else if (strcmp(operacao, "BORDAS") == 0) {
            if (mat1 == 'A' && mat1 != mat2)
                borda(a, b, len);
            else if (mat1 == 'B' && mat1 != mat2)
                borda(b, a, len);
            else if (mat1 == 'A')
                borda(a, a, len);
            else
                borda(b, b, len);
        
        } else {
            scanf(" %c", &mat3);

            if (mat1 == 'A' && mat2 == 'A' && mat3 == 'A') {
                if (strcmp(operacao, "SOMA") == 0)
                    soma(a, a, a, len);
                else if (strcmp(operacao, "MUlTI_ELEM") == 0)
                    multiElem(a, a, a, len);
                else
                    multiMat(a, a, a, len);

            } else if (mat1 == 'A' && mat2 == 'A' && mat3 == 'B') {
                if (strcmp(operacao, "SOMA") == 0)
                    soma(a, a, b, len);
                else if (strcmp(operacao, "MUlTI_ELEM") == 0)
                    multiElem(a, a, b, len);
                else
                    multiMat(a, a, b, len);

            } else if (mat1 == 'B' && mat2 == 'B' && mat3 == 'A') {
                if (strcmp(operacao, "SOMA") == 0)
                    soma(b, b, a, len);
                else if (strcmp(operacao, "MUlTI_ELEM") == 0)
                    multiElem(b, b, a, len);
                else
                    multiMat(b, b, a, len);

            } else if (mat1 == 'B' && mat2 == 'B' && mat3 == 'B') {
                if (strcmp(operacao, "SOMA") == 0)
                    soma(b, b, b, len);
                else if (strcmp(operacao, "MUlTI_ELEM") == 0)
                    multiElem(b, b, b, len);
                else
                    multiMat(b, b, b, len);

            } else if (mat1 != mat2) {
                if (mat3 == 'A') {

                    if (strcmp(operacao, "SOMA") == 0)
                        soma(a, b, a, len);
                    else if (strcmp(operacao, "MUlTI_ELEM") == 0)
                        multiElem(a, b, a, len);
                    else if (mat1 == 'A')
                        multiMat(a, b, a, len);
                    else
                        multiMat(b, a, a, len);

                } else {
                    if (strcmp(operacao, "SOMA") == 0)
                        soma(a, b, b, len);
                    else if (strcmp(operacao, "MUlTI_ELEM") == 0)
                        multiElem(a, b, b, len);
                    else if (mat1 == 'A')
                        multiMat(a, b, b, len);
                    else
                        multiMat(b, a, b, len);
                }
            }
        }
    }
    return 0;
}