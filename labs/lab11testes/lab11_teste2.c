#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PAI(i) ((i - 1)/2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)

typedef struct No *p_no;

struct No
{
    int v;
    p_no prox;  
};

typedef struct Grafo  *p_grafo;

struct Grafo 
{
    int n;
    p_no *adj; 
};

p_grafo criar_grafo (int n);

int * encontrar_caminhos (p_grafo g, int s);

void busca_em_profundiade (p_grafo g, int * pai,  int p, int v);

p_no inserir_lista (p_no lista, int v);

p_no remove_lista (p_no lista, int v);

void inserir_aresta (p_grafo g, int u, int v);

int distancia_entre_vertices (p_grafo g, int c, int p, int X);

void remove_aresta (p_grafo g, int u, int v);

void liberar_grafo (p_grafo g);

void liberar_lista (p_no lista);   

void insertionsort_v2(int *v, int n);

p_grafo criar_grafo (int n) {
    int i;
    p_grafo g = malloc (sizeof (struct Grafo));
    g -> n = n;
    g -> adj = malloc(n * sizeof(p_no));
    for (i = 0; i < n; i++) {
        g -> adj[i] = NULL;
    }
    return g;
}

p_no inserir_lista (p_no lista, int v) {
    p_no novo = malloc (sizeof (struct No));
    novo -> v = v;
    novo -> prox = lista;
    return novo; 
}

void inserir_aresta (p_grafo g, int u, int v) {
    g -> adj[v] = inserir_lista (g -> adj[v], u);
    g -> adj[u] = inserir_lista (g -> adj[u], v);
}

p_no remove_lista (p_no lista, int v) {
    p_no proximo;
    if (lista == NULL)
        return NULL;
    else if (lista->v == v) {
        proximo = lista -> prox;
        free(lista);
        return proximo;
    }   
    else {
        lista->prox = remove_lista(lista->prox, v);
        return lista;
    }
}

void remove_aresta (p_grafo g, int u, int v) {
    g -> adj[v] = remove_lista(g -> adj[v], u);
    g -> adj[u] = remove_lista(g ->adj[u], v); 
}

void busca_em_profundiade (p_grafo g, int * pai, int p, int v) {
    p_no t;
    pai[v] = p;
    for (t = g -> adj[v]; t!= NULL; t = t -> prox) {
        if (pai[t -> v] == -1)
            busca_em_profundiade(g, pai, v, t -> v);
    }
}

int * encontrar_caminhos(p_grafo g, int s) {
    int i, *pai = malloc (g -> n * sizeof(int));
    for(i = 0; i < g -> n; i++) {
        pai[i] = -1;
    }
    busca_em_profundiade(g, pai, s, s);
    return pai; 
}
 
int distancia_entre_vertices (p_grafo g, int c, int p, int X) {
    int *lista_pai = encontrar_caminhos(g, p);
    int i, contador = 0;
    for (i = c; i != -1; i = lista_pai[i]) {
        if (i == p)
            break;
        contador += 1;
    }
    if (contador <= X)
        printf("DISTANCIA %d -> %d = %d\n", c, p, contador);
    else if (contador > X) {
        printf("DISTANCIA %d -> %d = %d\n", c, p, contador);
        return 1;
    }
    return 0;
}

void insertionsort_v2(int *v, int n) {
    int i, j, t;
     for (i = 1; i < n; i++) {
        t = v[i];
        for (j = i; j > 0 && t < v[j-1]; j--)
            v[j] = v[j-1];
        v[j] = t;
    }
}

void liberar_lista (p_no lista) {
    if (lista != NULL) {
        liberar_lista(lista->prox);
        free(lista);
    }
}

void liberar_grafo (p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++)
        liberar_lista(g->adj[i]);
    free(g->adj);
    free(g);
} 

int main ()
{
    int c, p;
    scanf("%d %d", &c, &p);

    int n = c + p;
    p_grafo g;
    g = criar_grafo (n);

    int i, E, v1, v2;
    scanf("%d", &E);
    for (i = 0; i < E; i++) {
        scanf("%d %d", &v1, &v2);
        inserir_aresta (g, v1, v2);
    }

    printf ("GRAFO AMZ CONSTRUIDO!\n");

    int k, Q, X, vertice_c, vertice_p;
    char O;
    scanf ("%d", &Q);
    for (k = 0; k < Q; k++) {
        scanf(" %c %d %d", &O, &vertice_c, &vertice_p);
        if (O == 'D') {
            scanf("%d", &X);
            if (distancia_entre_vertices (g, vertice_c, vertice_p, X) == 1) {
                p_no vizinhos;
                p_grafo g_aux;
                int j = 0, percorrer;
                int *lista_ordenada = malloc ((n + 1) * sizeof(int)); /*lista ordenada em ordem crescente dos vertices a serem impressos*/
                n += 1;
                g_aux = g;

                g = criar_grafo(n);
                for (percorrer = 0; percorrer < g_aux -> n; percorrer++) {
                    g -> adj[percorrer] = g_aux -> adj[percorrer];
                }

                for (vizinhos = g -> adj[vertice_p]; vizinhos != NULL; vizinhos = vizinhos -> prox) {
                    lista_ordenada[j] = vizinhos-> v;
                    j++;
                    inserir_aresta(g, n - 1, vizinhos -> v);
                }
                lista_ordenada[j] = vertice_p;
                insertionsort_v2(lista_ordenada, j + 1);

                inserir_aresta(g, n - 1, vertice_p);

                printf("%d ADICIONADO E CONECTADO A ", (n - 1));
                for (percorrer = 0; percorrer < j; percorrer++) {
                    printf("%d ", lista_ordenada[percorrer]);
                }
                printf("%d\n", lista_ordenada[j]);
            }
        }

        else if (O == 'R') {
            remove_aresta(g, vertice_c, vertice_p);
            printf("ARESTA %d -> %d REMOVIDO\n", vertice_c, vertice_p);
        }
    }
}