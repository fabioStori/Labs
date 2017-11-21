#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {Red, Blue, Green} Imperio;

typedef struct IlhasGreen {
    char nome[30];
    int custo;
} IlhasGreen;

typedef struct No{
    //Imperio imperio;
    int distancia;
    char nome[30];
    struct No *prox;
}No;

typedef struct Grafo{
    int quantIlhas;
    No **adj;
}Grafo;

void iniciaGrafo(Grafo *g, int n, IlhasGreen *ilhasGreen);

No * insereNaLista(No *lista , int vert, char nome[30], int distancia);

void insereAresta(Grafo g, int i, int j, int distancia);

int achaIndice(Grafo g, char nome[30], int L);

void imprimir(Grafo g, int L);

int *dijkstra(Grafo g, int s);

int main() {
    int i, distancia, limBlue, limRed, L; //L é o numero de ilhas que o Green tem inicialmente
    char ilha1[30], ilha2[30];

    scanf("%d %d %d", &limRed, &limBlue, &L);
    IlhasGreen *ilhasGreen = malloc(sizeof(IlhasGreen*));

    for (i = 0; i < L; i++) {        
        scanf("%s %d", ilhasGreen[i].nome, &ilhasGreen[i].custo);
    }
    
    Grafo g;
    int quantIlhas = L+2;
    iniciaGrafo(&g, quantIlhas, ilhasGreen);
    
    while (scanf("%s %s %d", ilha1, ilha2, &distancia) != EOF) {
        if(!(strcmp(ilha1, "Red"))){
            printf("red\n");
            insereAresta(g, 0, achaIndice(g, ilha2, quantIlhas), distancia);
            //insere aresta da ilha green ligada ao red
        }else if(!(strcmp(ilha1, "Blue"))){
            printf("blue\n");
            insereAresta(g, 1, achaIndice(g, ilha2, quantIlhas), distancia);
            //insere aresta da ilha green ligada ao blue
        }else{
            printf("green\n");
            insereAresta(g, achaIndice(g, ilha1, quantIlhas), achaIndice(g, ilha2, quantIlhas), distancia);
            //insere aresta da ilha green liga a outra green
        }
    }
    imprimir(g, quantIlhas);
    //quando termina de inserir as arestas no grafo (lista de adjacencias)
    //começa os testes

    return 0;
}

void iniciaGrafo(Grafo *g, int n, IlhasGreen *ilhasGreen) {
    int i, j=0;
    //printf("ilhagreen: %s\n", ilhasGreen[1].nome);
    //char nome[30]; strcpy(nome, ilhasGreen[1].nome);
    g->quantIlhas = n;
    g->adj = malloc(n * sizeof(No *));
    for (i = 0; i < n; i++){
        g->adj[i] = malloc(sizeof(No));
        g->adj[i]->prox = NULL;
        g->adj[i]->distancia = -1;
        if(i==0){
            strcpy(g->adj[i]->nome, "Red");  strcpy(g->adj[i]->nome, "Red");
            printf("red %s\n", g->adj[i]->nome);
        }else if(i==1){
            strcpy(g->adj[i]->nome, "Blue"); strcpy(g->adj[i]->nome, "Blue");
            printf("blue %s\n", g->adj[i]->nome);
        }else{
            strcpy(g->adj[i]->nome, ilhasGreen[i-2].nome); strcpy(g->adj[i]->nome, ilhasGreen[i-2].nome);
            printf("green %s\n", g->adj[i]->nome);
        }
    }
}

No * insereNaLista(No *lista , int vert, char nome[30], int distancia) {
    No *novo = malloc(sizeof(No));
    novo->distancia = distancia;
    strcpy(novo->nome, nome);
    novo->prox = lista;
    return novo;
}

void insereAresta(Grafo g, int i, int j, int distancia) {
    printf("i: %d j: %d\n", i, j);
    g.adj[i] = insereNaLista(g.adj[i], j, g.adj[j]->nome, distancia);
    //g.adj[j] = insereNaLista(g.adj[j], i, g.adj[i]->nome, distancia);
}

int achaIndice(Grafo g, char nome[30], int L){
    int i; No *tmp;
    for(i=0;i<L;i++){
        tmp=g.adj[i];
        while(tmp->prox!=NULL)
            tmp=tmp->prox;
        if(strcmp(tmp->nome, nome)==0){
            printf("nome indice %s\n", tmp->nome);
            return i;
        }
    }
    return -1;
}

void imprimir(Grafo g, int L){
    int i;
    for(i=0;i<L;i++){
        if(g.adj[i]->prox!=NULL){
            No* tmp = g.adj[i];
            while(tmp!=NULL){
                printf("indice [%d] nome [%s] distancia [%d]\n", i, tmp->nome, tmp->distancia);
                tmp=tmp->prox;
            }
        }else{
            printf("indice [%d] nome [%s] distancia [%d]\n", i, g.adj[i]->nome, g.adj[i]->distancia);
        }printf("\n");
    }
}
/*
int *dijkstra(Grafo g, int s) {
    int v, *pai = malloc(g.n * sizeof(int));
    No *t; FilaP h;
    inicializa(&h, g.n); // inicializa heap
    for (v = 0; v < g.n; v++) {
        pai[v] = -1; // inicializa vertices pai
        insere(&h, v, INT_MAX); // vértices no heap
    }
    pai[s] = s; // pai do raiz é a raiz
    diminuiprioridade (&h, s, 0); // prioridade da raiz
    while (!vazia(&h)) {
        v = extrai_minimo(&h);
        // vértice já acessado - 'distância não infinita'
        if (prioridade(&h, v) != INT_MAX){
            // acessa os adjacentes
            for (t = g.adj[v]; t != NULL; t = t->prox){
                // se o caminho é minimizado via t (adjancente)
                if (prioridade(&h, v)+t->peso < prioridade(&h, t->v)){
                    // atualiza prioridade do vértice t
                    diminuiprioridade(&h,t->v,prioridade(&h,v)+t->peso);
                    pai[t->v] = v; // atualiza pai do vértice t
                }
            }
        }
    }
    return pai;
}*/
