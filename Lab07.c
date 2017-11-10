/*
  Lab07: Painel de Controle de Programas
  Nome: Fabio Stori
  RA: 196631
  Nome: Adivair Satana Ramos
  RA: 193325
  Turma E - MC202
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef enum {Esq, Dir, Raiz} Filho;

typedef struct Pasta{
    struct Pasta *dir;
    struct Pasta *esq;
    struct Pasta *pai;
    char programa[30];
    char nome[34];
}Pasta;

Pasta* inserir (Pasta *pasta, char programa[30]);

void alocar (Pasta *pasta, char programa[30], Filho filho);

void imprimeInOrdem(Pasta *pasta);

void inicializaRaiz(Pasta *raiz);

char **alocaMatriz(int lin, int col);

Pasta *constrArv(char **inOrdem, char **preOrdem, int l, int r, int *indPre, Pasta *pai, Filho filho);

int  main(){
    int op, P, i;
    scanf("%d", &P);
    Pasta *raiz;
    //= malloc(sizeof(Pasta));
    //inicializaRaiz(raiz);
    //raiz = NULL;
    char **inOrdem, **preOrdem, programa[30];
    inOrdem = alocaMatriz(P, 30);
    preOrdem = alocaMatriz(P, 30);
    for(i=0;i<P;i++)
        scanf("%s", inOrdem[i]);
    for(i=0;i<P;i++)
        scanf("%s", preOrdem[i]);
    int indPre = 0;
    raiz = constrArv(inOrdem, preOrdem, 0, P, &indPre, NULL, Raiz);

    while(scanf("%d", &op)!= EOF){    //ate o arquivo acabar...

        switch(op){
            case(1):
                scanf("%s", programa);
                raiz = inserir(raiz, programa);
                break;

            case(2):
                break;

            case(3):
                break;

            case(4):
                break;

            case(5):
                break;

            case(6):
                break;

            case(7):
                imprimeInOrdem(raiz);
                break;
        }
    }
    return 0;
}
void inicializaRaiz(Pasta *raiz) {
    raiz->pai = NULL;
    raiz->dir = NULL;
    raiz->esq = NULL;
}
Pasta* inserir (Pasta *pasta, char programa[30]){
    if(pasta){
        int teste = strcmp(programa, pasta->programa);    //testa se o programa e maior ou menor
        if(teste<0){      //se for menor, vai pra esquerda
            if(pasta->esq == NULL)    //e se o da esquerda for nulo, insere
                alocar(pasta, programa, Esq);
                else
                    inserir(pasta->esq, programa);    //se nao, testa o da esquerda
            }else{      //se nao for menor, é maior, logo executa um procedimento analogo para a direita
                if(pasta->dir == NULL)
                    alocar(pasta, programa, Dir);
                else
                    inserir(pasta->dir, programa);
        }
        return pasta;
    }else{    //caso em que a arvore esta vazia
        Pasta *novo = malloc(sizeof(Pasta));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->pai = NULL;
        strcpy(novo->nome, "raiz");
        strcpy(novo->programa, programa);
        novo;
            return novo;
    }
}

    void alocar (Pasta *pasta, char programa[30], Filho filho){
        Pasta *novo = malloc(sizeof(Pasta));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->pai = pasta;
        strcpy(novo->nome, pasta->programa);
        strcpy(novo->programa, programa);
        if(filho == Esq){
            strcat(novo->nome, "_esq");
            pasta->esq = novo;
        }else if(filho == Dir){
            strcat(novo->nome, "_dir");
            pasta->dir = novo;
        }
    }
void imprimeInOrdem(Pasta *pasta){
    if(pasta){
        imprimeInOrdem(pasta->esq);
        printf("Programa: %s | Pasta: %s\n", pasta->programa, pasta->nome);
        imprimeInOrdem(pasta->dir);

    }
}
char **alocaMatriz(int lin, int col){
    char **m = (char**) malloc(lin*sizeof(char *));
    for(int i = 0; i < lin; i++){
        m[i] = (char*) malloc(col*sizeof(char));
        for(int j = 0; j < col; j++)
            m[i][j] = 'A';
    }
    return m;
}

void imprimeMat(char **mat, int lin, int col){
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++)
            printf("%c ", mat[i][j]);
        printf("\n");
    }

}

Pasta *constrArv(char **inOrdem, char **preOrdem, int l, int r, int *indPre, Pasta *pai, Filho filho){
    if(l < r) {
        char prog[30];
        strcpy(prog, preOrdem[(*indPre)++]);
        int i = l;
        while (strcmp(prog, inOrdem[i]))
            i++;
        Pasta *novo = malloc(sizeof(Pasta));
        strcpy(novo->programa, prog);
        if(pai){
            novo->pai = pai;
            strcpy(novo->nome, pai->programa);
            if(filho == Esq)
                strcat(novo->nome, "_esq");
            if(filho == Dir)
                strcat(novo->nome, "_dir");
        }
        else
            strcpy(novo->nome, "raiz");
        novo->esq = constrArv(inOrdem, preOrdem, l, i, indPre, novo, Esq);
        novo->dir = constrArv(inOrdem, preOrdem, i+1, r, indPre, novo, Dir);
        return novo;
    }
    else
        return NULL;
}
