#include <stdio.h>
#include <stdlib.h>

typedef struct no *p_no;

struct no {
    int v;
    p_no prox;
};

typedef struct grafo *p_grafo;

struct grafo {
    p_no adjacencia[100];
    int qtd_P;
    int qtd_C;
    int n;
};

typedef struct fila *p_fila;

struct fila {
    p_no ini, fim;
};

p_grafo criar_grafo(int qtd_P, int qtd_C) {
    int i;
    int n = qtd_P + qtd_C;
    p_grafo g = malloc(sizeof(struct grafo));
    g->qtd_P = qtd_P;
    g->qtd_C = qtd_C;
    g->n = n;
    for (i = 0; i < n; i++)
        g->adjacencia[i] = NULL;
    printf("GRAFO AMZ CONSTRUIDO!\n");
    return g;
}

void libera_lista(p_no lista) {
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++)
        libera_lista(g->adjacencia[i]);
    free(g);    
}

p_no insere_na_lista(p_no lista, int v) {
    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void insere_aresta(p_grafo g, int u, int v) {
    g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
    g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
}

p_no remove_da_lista(p_no lista, int v) {
    p_no proximo;
    if (lista == NULL)
        return NULL;
    else if (lista->v == v) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    } else {
        lista->prox = remove_da_lista(lista->prox, v);
        return lista;
    }
}

void remove_aresta(p_grafo g, int u, int v) {
    g->adjacencia[u] = remove_da_lista(g->adjacencia[u], v);
    g->adjacencia[v] = remove_da_lista(g->adjacencia[v], u);
    printf("ARESTA %d -> %d REMOVIDO\n", u, v);
}

int tem_aresta(p_grafo g, int u, int v) {
    p_no t;
    for (t = g->adjacencia[u]; t != NULL; t = t->prox)
        if (t->v == v)
            return 1;
    return 0;
}

p_fila criar_fila() {
    p_fila f;
    f = malloc(sizeof(struct fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void destruir_fila(p_fila f) {
    libera_lista(f->ini);
    free(f);
}

void enfileira(p_fila f, int x) {
    p_no novo;
    novo = malloc(sizeof(struct no));
    novo->v = x;
    novo->prox = NULL;
    if (f->ini == NULL)
        f->ini = novo;
    else
        f->fim->prox = novo;
    f->fim = novo;
}

int desenfileira(p_fila f) {
    p_no primeiro = f->ini;
    int x = primeiro ->v;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    free(primeiro);
    return x;
}

int fila_vazia(p_fila f) {
    if (f->ini == NULL)
        return 1;
    return 0;
}

int sao_adjacentes(p_grafo g, int w, int v) {
    p_no aux = g->adjacencia[w];
    while (aux != NULL) {
        if (aux->v == v)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

int * busca_em_largura(p_grafo g, int s) {
    int w, v;
    int *pai = malloc(g->n * sizeof(int));
    int *visitado = malloc(g->n * sizeof(int));
    p_fila f = criar_fila();
    for (v = 0; v < g->n; v++) {
        pai[v] = -1;
        visitado[v] = 0;
    }
    enfileira(f,s);
    pai[s] = s;
    visitado[s] = 1;
    while(!fila_vazia(f)) {
        v = desenfileira(f);
        for (w = 0; w < g->n; w++)
        if (sao_adjacentes(g, w, v) && !visitado[w]) {
            visitado[w] = 1;/*evita repetição na fila*/
            pai[w] = v;
            enfileira(f, w);
        }
    }
    destruir_fila(f);
    free(visitado);
    return pai;
}

void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int extrai_maximo(int *v, int n) {
    int j, max = n - 1;
    for (j = n - 2; j >= 0; j--)
        if (v[j] > v[max])
            max = j;
    return max;
}

void ordena_vetor(int *v, int n) {
    int i, max;
    for (i = n - 1; i > 0; i--) {
        max = extrai_maximo(v, i + 1);
        troca(&v[i], &v[max]);
    }
}

void imprime_vizinhos_novo_no(p_grafo g, int novo_no) {
    p_no vizinho = g->adjacencia[novo_no];
    int vizinhos[30], tamanho_vizinhos, i;
    for (i = 0; vizinho != NULL; i++, vizinho = vizinho->prox)
        vizinhos[i] = vizinho->v;
    tamanho_vizinhos = i;
    ordena_vetor(vizinhos, tamanho_vizinhos);
    printf("%d ADICIONADO E CONECTADO A", novo_no);
    for (i = 0; i < tamanho_vizinhos; i++)
        printf(" %d", vizinhos[i]);
    printf("\n");
}

void adiciona_no(p_grafo g, int v) {
    int novo_no = g->n;
    p_no vizinho_v = g->adjacencia[v];
    while (vizinho_v != NULL) {
        insere_aresta(g, novo_no, vizinho_v->v);
        vizinho_v = vizinho_v->prox;
    }
    insere_aresta(g, novo_no, v);
    g->n++;
    imprime_vizinhos_novo_no(g, novo_no);
}

void calcula_distancia(p_grafo g, int v, int w, int distancia_adicao) { // calcula distância para chegar de v a w
    int *pai = busca_em_largura(g, w);
    int distancia = 0, proximo_pai = v;
    while (proximo_pai != w) {
        proximo_pai = pai[proximo_pai];
        distancia++;
    }
    printf("DISTANCIA %d -> %d = %d\n", w, v, distancia);
    free(pai);
    if (distancia > distancia_adicao)
        adiciona_no(g, v);
}

int main() {
    int i, qtd_C, qtd_P, E, V1, V2, Q, C, P, distancia_adicao;
    char operacao;
    p_grafo g;
    scanf("%d", &qtd_C);
    scanf("%d", &qtd_P);
    g = criar_grafo(qtd_P, qtd_C);
    scanf("%d", &E);
    for (i = 0; i < E; i++) {
        scanf("%d", &V1);
        scanf("%d", &V2);
        insere_aresta(g, V1, V2);
    }
    scanf("%d", &Q);
    for (i = 0; i < Q; i++) {
        scanf(" %c ", &operacao);
        scanf("%d", &C);
        scanf("%d", &P);
        if (operacao == 'D') {
            scanf("%d", &distancia_adicao);
            calcula_distancia(g, P, C, distancia_adicao);
        } else {
            remove_aresta(g, C, P);
        }
    }
}