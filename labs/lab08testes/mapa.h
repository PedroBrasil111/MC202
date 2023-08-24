/* ÁRVORE MAPA */

typedef struct Mapa *p_mapa; //ponteiro para nó da árvore mapa

struct Mapa {               //struct do nó da árvore mapa (ordenação por nome da cidade)
    char *cidade;           //nome da cidade
    int qtdeVis;            //quantidade de visitas
    p_mapa esq, dir, pai;   //nós para esquerda, direita e pai
};

/* Cria a árvore mapa sem nós */
p_mapa criar_mapa();

/* Insere a cidade na árvore mapa */
p_mapa inserir_mapa(p_mapa raiz, char *cidade);

/* Reduz a quantidade de visitas da cidade na árvore mapa, e a remove se qtdeVis = 0 */
p_mapa remover_mapa(p_mapa raiz, char *cidade);

/* Libera a árvore mapa */
void destruir_mapa(p_mapa raiz);

/* ÁRVORE VISITA */

typedef struct Visita *p_vis; //ponteiro para nó da árvore visita

struct Visita {             //struct da nó da árvore visita (ordenação por data)
    char *cidade;           //nome da cidade
    int data, pista;        //data: data de visita, pista: 0 se houver, 1 se não houver pista
    p_vis esq, dir, pai;    //nós para esquerda, direita e pai
};

/* Cria a árvore visitas sem nós */
p_vis criar_visita();

/* Insere a data na árvore visita */
p_vis inserir_visita(p_vis raiz, int data, int pista, char *cidade);

/* Remove o nó referente à data; cidadeRemov: nome da cidade que foi removida */
p_vis remover_visita(p_vis raiz, int data, char *cidadeRemov);

/* Imprime as visitas entre dataIni e dataFim em ordem crescente de data */
void relatorio_data(p_vis raiz, int dataIni, int dataFim);

/* Imprime as visitas com pista entre dataIni e dataFim em ordem decrescente de data */
void relatorio_pista(p_vis raiz, int dataIni, int dataFim);

/* Libera a árvore visita */
void destruir_visita(p_vis raiz);