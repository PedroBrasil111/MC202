typedef struct {
    char nome[100];
    float nivelMax;
    int medidas[1000], qtdMedidas, media;
    //medidas - vetor c/ os níveis medidos, qtdMedidas - tamanho do vetor, media - media dos níveis
} Represa;

/* Cria e retorna uma represa após ler suas informações */
Represa leRepresa();

/* Padroniza o nome das represas no vetor r, len - tamanho de r */
void padronizaNome(Represa *r, int len);

/* Imprime as informações da represa */
void relatorioRepresa(Represa r);