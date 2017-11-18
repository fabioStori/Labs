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

int main() {
    int i, distancia, limBlue, limRed, L; //L é o numero de ilhas que o Green tem inicialmente
    char imperio[30], ilha[30];

    scanf("%d %d %d", &limRed, &limBlue, &L);
    IlhasGreen *ilhasGreen;
    
    for (i = 0; i < L; i++) {
        //ilhasGreen[i] = malloc(sizeof(IlhasGreen));
        scanf("%s %d", ilhasGreen[i].nome, &ilhasGreen[i].custo);
    }
    Grafo g;
    int quantIlhas = L+2;
    iniciaGrafo(&g, quantIlhas, ilhasGreen);

    while (scanf("%s %s %d", imperio, ilha, &distancia) != EOF) {
        if(!(strcmp(imperio, "Red"))){
            //insere aresta da ilha green ligada ao red
        }else if(!(strcmp(imperio, "Blue"))){
            //insere aresta da ilha green ligada ao blue
        }else{
            //insere aresta da ilha green liga a outra green
        }
    }
    //quando termina de inserir as arestas no grafo (lista de adjacencias)
    //começa os testes

    return 0;
}

void iniciaGrafo(Grafo *g, int n, IlhasGreen *ilhasGreen) {
    int i;
    g->quantIlhas = n;
    g->adj = malloc(n * sizeof(No *));
    for (i = 0; i < n; i++){
        g->adj[i]->prox = NULL;/*
        g->adj[i]->distancia = -1;
        if(i==0)
            strcpy(g->adj[i]->nome, "Red");
        else if(i==1)
            strcpy(g->adj[i]->nome, "Blue");
        else{
            strcpy(g->adj[i]->nome, ilhasGreen[i].nome);
        }*/
    }
}
/*
No * insereNaLista(No *lista , int vert) {
    No *novo = malloc(sizeof(No));
    novo ->v = vert;
    novo ->prox = lista;
    return novo;
}

void insereAresta(Grafo g, int i, int j) {
    g.adj[i] = insereNaLista(g.adj[i], j);
    g.adj[j] = insereNaLista(g.adj[j], i);
}*/
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







