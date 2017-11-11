/*
  Lab07: Painel de Controle de Programas
  Nome: Fabio Stori
  RA: 196631
  Nome: Adivair Santana Ramos
  RA: 193325
  Turma E - MC202
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <math.h>

int NUM_PROG;

typedef enum {Esq, Dir, Raiz} Filho;

typedef struct Pasta{
    struct Pasta *dir;
    struct Pasta *esq;
    struct Pasta *pai;
    char programa[30];
    char nome[34];
}Pasta;

Pasta* inserir (Pasta *pasta, char programa[30]);

void alocarPasta (Pasta *pasta, char programa[30], Filho filho);

void imprimeInOrdem(Pasta *pasta);

void imprimePreOrdem(Pasta *pasta);

char **alocaMatriz(int lin, int col);

void imprimeMat(char **mat, int lin, int col);

Pasta *constrArv(char **inOrdem, char **preOrdem, int l, int r, int *indPre, Pasta *pai, Filho filho);

int nivelPrograma(Pasta *raiz, char *busca, int nivel);

Pasta* remover(Pasta *pasta, char programa[30]);

void substituirAntecessor(Pasta *pasta);

void testeVelocidade(int t_gasto, int t_max, char *prog);

Pasta* balanceamento(Pasta *raiz);

void extraiSemente(Pasta *raiz, char **aux, int *indice);

Pasta *criaArv(char **semente, int l, int r, Filho filho, Pasta *pai);

void desaloca(Pasta *raiz);

void extraiSementePre(Pasta *raiz, char **aux, int *ind);

void criaCopia(Pasta *raiz, char **in, char **pre);

int altura(Pasta *raiz);

void imprime(Pasta *raiz);

void imprimeCaminho(Pasta *raiz, char *dire);

int  main() {
    int op, P, i, tempo, nivel, NUM_PROG_BACKUP;
    scanf("%d", &P);
    Pasta *raiz;
    NUM_PROG = P;
    //= malloc(sizeof(Pasta));
    //inicializaRaiz(raiz);
    //raiz = NULL;
    char **inOrdem, **preOrdem, programa[30], **inSeg, **preSeg;
    inOrdem = alocaMatriz(P, 30);
    preOrdem = alocaMatriz(P, 30);
    for (i = 0; i < P; i++)
        scanf("%s", inOrdem[i]);
    for (i = 0; i < P; i++)
        scanf("%s", preOrdem[i]);
    int indPre = 0;
    raiz = constrArv(inOrdem, preOrdem, 0, P, &indPre, NULL, Raiz);

    while (scanf("%d", &op) != EOF) {    //ate o arquivo acabar...

        switch (op) {
            case (1):
                scanf("%s", programa);
                raiz = inserir(raiz, programa);
                NUM_PROG++;
                break;

            case (2):
                scanf("%s", programa);
                raiz = remover(raiz, programa);
                NUM_PROG--;
                break;

            case (3):
                scanf("%s %d", programa, &tempo);
                testeVelocidade(nivelPrograma(raiz, programa, 0), tempo, programa);
                break;

            case (4):
                raiz = balanceamento(raiz);
                break;

            case (5):
                inSeg = alocaMatriz(NUM_PROG, 30);
                preSeg = alocaMatriz(NUM_PROG, 30);
                NUM_PROG_BACKUP = NUM_PROG;
                //printf("%d", NUM_PROG);
                criaCopia(raiz, inSeg, preSeg);
                //imprimeMat(preSeg, NUM_PROG, 30);
                //imprimeMat(inSeg, NUM_PROG, 30);
                break;

            case (6):
                indPre = 0;
                raiz = constrArv(inSeg, preSeg, 0, NUM_PROG_BACKUP, &indPre, NULL, Raiz);
                printf("[RESTORE] Sistema restaurado para a versao do backup\n");
                break;

            case (7):
                imprime(raiz);
                break;

            case (8):
                imprimeInOrdem(raiz);
                printf("Total de Prog: %d \n", NUM_PROG);
                break;
            default:
                break;
        }
    }
}

Pasta* remover(Pasta *pasta, char programa[30]){
    if(pasta == NULL)
        return NULL;
    if((strcmp(pasta->nome, "raiz")) == 0 && pasta->esq == NULL && pasta->dir == NULL){   //caso em que existe apenas a raiz sem filhos
        free(pasta);
        return NULL;
    }
    int teste = strcmp(programa, pasta->programa);
    if(teste<0){
        pasta->esq = remover(pasta->esq, programa);
        if(pasta->esq != NULL){
            strcpy(pasta->esq->nome, pasta->programa);
            strcat(pasta->esq->nome, "_esq");
        }
        return pasta;
    }else if(teste>0){
        pasta->dir = remover(pasta->dir, programa);
        if(pasta->dir != NULL){
            strcpy(pasta->dir->nome, pasta->programa);
            strcat(pasta->dir->nome, "_dir");
        }
        return pasta;
    }else if (pasta->esq == NULL){
        Pasta *tmp = pasta->dir;
        free(pasta);
        return tmp;
    }else if (pasta->dir == NULL){
        Pasta *tmp = pasta->esq;
        free(pasta);
        return tmp;
    }else{
        substituirAntecessor(pasta);
        return pasta;
    }
}

void substituirAntecessor (Pasta *pasta){
    Pasta *pai = pasta, *t = pasta->esq;
    while(t->dir!=NULL){
        pai = t;
        t = t->dir;
    }
    if(pai->esq == t)
        pai->esq = t->dir;
    else
        pai->dir = t->esq;
    strcpy(pasta->programa, t->programa);
    free(t);
    printf("Programa: %s, Pasta: %s | removidos\n", pasta->programa, pasta->nome);
}

Pasta* inserir (Pasta *pasta, char programa[30]){
    if(pasta){

        int teste = strcmp(programa, pasta->programa);    //testa se o programa e maior ou menor
        if (teste < 0) {      //se for menor, vai pra esquerda
            if (pasta->esq == NULL)    //e se o da esquerda for nulo, insere
                alocarPasta(pasta, programa, Esq);
            else
                inserir(pasta->esq, programa);    //se nao, testa o da esquerda
        } else {      //se nao for menor, é maior, logo executa um procedimento analogo para a direita
            if (pasta->dir == NULL)
                alocarPasta(pasta, programa, Dir);
            else
                inserir(pasta->dir, programa);
        }
        return pasta;
    } else {    //caso em que a arvore esta vazia
        Pasta *novo = malloc(sizeof(Pasta));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->pai = NULL;
        strcpy(novo->nome, "raiz");
        strcpy(novo->programa, programa);
        printf("[INSTALL] Programa %s.exe instalado com sucesso na pasta %s\n", novo->programa, novo->nome);
        return novo;
    }
}

void alocarPasta(Pasta *pasta, char programa[30], Filho filho) {
    Pasta *novo = malloc(sizeof(Pasta));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = pasta;
    strcpy(novo->nome, pasta->programa);
    strcpy(novo->programa, programa);
    if (filho == Esq) {
        strcat(novo->nome, "_esq");
        pasta->esq = novo;
    } else if (filho == Dir) {
        strcat(novo->nome, "_dir");
        pasta->dir = novo;
    }
    printf("[INSTALL] Programa %s.exe instalado com sucesso na pasta %s\n", novo->programa, novo->nome);
}

void imprimeInOrdem(Pasta *pasta) {
    if (pasta) {
        imprimeInOrdem(pasta->esq);
        printf("Programa: %s | Pasta: %s\n", pasta->programa, pasta->nome);
        imprimeInOrdem(pasta->dir);
    }
}

void imprimePreOrdem(Pasta *pasta) {
    if (pasta) {
        printf("Programa: %s | Pasta: %s\n", pasta->programa, pasta->nome);
        imprimeInOrdem(pasta->esq);
        imprimeInOrdem(pasta->dir);
    }
}
char **alocaMatriz(int lin, int col) {
    char **m = (char **) malloc(lin * sizeof(char *));
    for (int i = 0; i < lin; i++) {
        m[i] = (char *) malloc(col * sizeof(char));
        for (int j = 0; j < col; j++)
            m[i][j] = ' ';
    }
    return m;
}
void imprimeMat(char **mat, int lin, int col) {
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++)
            printf("%c ", mat[i][j]);
        printf("\n");
    }
}

Pasta *constrArv(char **inOrdem, char **preOrdem, int l, int r, int *indPre, Pasta *pai, Filho filho) {
    if (l < r) {
        char prog[30];
        strcpy(prog, preOrdem[(*indPre)++]);
        int i = l;
        while (strcmp(prog, inOrdem[i]))
            i++;
        Pasta *novo = malloc(sizeof(Pasta));
        strcpy(novo->programa, prog);
        novo->pai = pai;//Atualizei mas ainda não testei, se der merda coloque essa linha dentro de if(pai)
        if (pai) {
            strcpy(novo->nome, pai->programa);
            if (filho == Esq)
                strcat(novo->nome, "_esq");
            if (filho == Dir)
                strcat(novo->nome, "_dir");
        } else
            strcpy(novo->nome, "raiz");
        novo->esq = constrArv(inOrdem, preOrdem, l, i , indPre, novo, Esq);
        novo->dir = constrArv(inOrdem, preOrdem, i + 1, r, indPre, novo, Dir);
        return novo;
   } else
        return NULL;
}

int nivelPrograma(Pasta *raiz, char *busca, int nivel) {
    if (raiz == NULL)
        return -1;
    if (!strcmp(raiz->programa, busca))
        return nivel;
    int esquerda = nivelPrograma(raiz->esq, busca, nivel + 1);
    int direita = nivelPrograma(raiz->dir, busca, nivel + 1);

    if (esquerda == -1)
        return direita;
    else
        return esquerda;
}
void testeVelocidade(int t_gasto, int t_max, char *prog) {
    if (t_gasto > t_max)
        printf("[DELAY][FAIL] O acesso ao programa %s.exe ultrapassou o limite de %d segundo\n", prog, t_max);
    else
        printf("[DELAY][OK] O acesso ao programa %s.exe foi concluido em %d segundos\n", prog, t_gasto);
}

Pasta* balanceamento(Pasta *raiz) {
    int indice=0;
    char **aux = alocaMatriz(NUM_PROG, 30);
    extraiSemente(raiz, aux, &indice);
    //imprimeMat(aux, NUM_PROG, 30);
    desaloca(raiz);
    raiz = criaArv(aux, 0, NUM_PROG-1, Raiz, NULL);
    //imprimePreOrdem(raiz);
    printf("[OPTIMIZE] O sistema de acesso a programas foi otimizado\n");
    return raiz;
}
void extraiSemente(Pasta *raiz, char **aux, int *indice){
    if(raiz){
        //strcpy(aux[(*indice)++], raiz->programa);
        extraiSemente(raiz->esq, aux, indice);
        strcpy(aux[(*indice)++], raiz->programa);
        extraiSemente(raiz->dir, aux, indice);
        //strcpy(aux[(*indice)++], raiz->programa);
    }
}
Pasta *criaArv(char **semente, int l, int r, Filho filho, Pasta *pai){
    if (r > l) {
        float meio = l + ((float)r-(float)l)/2;
        Pasta *novo = malloc(sizeof(Pasta));
        strcpy(novo->programa, semente[(int)meio]);
        novo->pai = pai;
        if (pai) {
            strcpy(novo->nome, pai->programa);
            if (filho == Esq)
                strcat(novo->nome, "_esq");
            if (filho == Dir)
                strcat(novo->nome, "_dir");
        } else
            strcpy(novo->nome, "raiz");

        novo->esq = criaArv(semente, l, (int)meio-1, Esq, novo);
        novo->dir = criaArv(semente, (int)meio+1, r, Dir, novo);
        return novo;
    }
    else if(l == r) {
        Pasta *novo = malloc(sizeof(Pasta));
        strcpy(novo->programa, semente[r]);
        novo->pai = pai;
        novo->esq = NULL;
        novo->dir = NULL;
        if (pai) {
            strcpy(novo->nome, pai->programa);
            if (filho == Esq)
                strcat(novo->nome, "_esq");
            if (filho == Dir)
                strcat(novo->nome, "_dir");
        } else
            strcpy(novo->nome, "raiz");
        return novo;
    }
    else
        return NULL;
}

void desaloca(Pasta *raiz) {
    if (raiz) {
        desaloca(raiz->esq);
        desaloca(raiz->dir);
        free(raiz);
    }
}

void extraiSementePre(Pasta *raiz, char **aux, int *ind){
    if(raiz){
        strcpy(aux[(*ind)++], raiz->programa);
        extraiSementePre(raiz->esq, aux, ind);
        extraiSementePre(raiz->dir, aux, ind);
    }
}

void criaCopia(Pasta *raiz, char **in, char **pre) {
    int indice1 = 0, indice2 = 0;
    extraiSemente(raiz, in, &indice1);
    extraiSementePre(raiz, pre, &indice2);
    printf("[BACKUP] Configuracao atual do sistema salva com sucesso\n");
}

void imprime(Pasta *raiz){
    char *diretorio = malloc(3*sizeof(char));
    strcpy(diretorio, "C:");
    printf("[PATHS]\n");
    imprimeCaminho(raiz, diretorio);
}

void imprimeCaminho(Pasta *raiz, char *dire){
    if(raiz) {
        char *atual = malloc((strlen(dire)+34)*sizeof(char));
        strcpy(atual, dire);
        strcat(atual, "/");
        strcat(atual, raiz->nome);
        imprimeCaminho(raiz->esq, atual);
        printf("%s/%s.exe\n", atual, raiz->programa);
        imprimeCaminho(raiz->dir, atual);
    }
}
