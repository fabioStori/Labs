/*
  Lab07: Painel de Controle de Programas
  Nome: Fabio Stori
  RA: 196631
  Nome: Adivair Santana Ramos
  RA: 193325
  Turma E - MC202
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int NUM_PROG;       //variavel global que controla a quantidade de programas na arvore

typedef enum {Esq, Dir, Raiz} Filho;        //tipos de pastas

typedef struct Pasta{
    struct Pasta *dir;
    struct Pasta *esq;
    struct Pasta *pai;
    char programa[30];  //nome do programa
    char nome[34];  //nome da pasta
}Pasta;

char **alocaMatriz(int lin, int col);
/*
Aloca dinamicamente uma matriz [lin X col]
lin: numero de linhas
col: numero de colunas
*/
Pasta *constrArv(char **inOrdem, char **preOrdem, int l, int r, int *indPre, Pasta *pai, Filho filho);
/*
Constroi uma arvore binaria de busca a partir de 2 sementes (inOrdem e preOrdem). Utilizado para gerar a arvore inicial
l: numero do indice mais a esquerda que sera considerado
r: numero do indice mais a direita que sera considerado
*indPre: guarda o indice da raiz pela semente preOrdem
*pai: ponteiro pro pai
filho: passa informacao se sera considerado i filho da esquerda ou da direita
*/
Pasta* inserir (Pasta *pasta, char programa[30]);
/*
Insere programa em uma arvore binaria de busca, seguindo o padrao de ordem lexigrafica
*pasta: ponteiro para a raiz da arvore binaria de busca
programa[30]: string com o nome do programa que sera inserido
*/
void alocarPasta (Pasta *pasta, char programa[30], Filho filho);
/*
Aloca um novo programa, atualizando o nome de sua pasta
*pasta: ponteiro para a raiz da arvore binaria de busca
programa[30]: string com o nome do programa que sera inserido
filho: lado da arvore que sera inserido
*/
Pasta* remover(Pasta *pasta, char programa[30]);
/*
Remove um programa e ajusta o nome das pastas da arvore binaria de busca
*pasta: ponteiro para a raiz da arvore binaria de busca
programa[30]: string que esta sendo buscada
*/
Pasta* buscar(Pasta *raiz, char programa[30]);
/*
Funcao que busca um determinado programa na arvore. Retorna NULL se nao acha tal programa
*raiz: ponteiro para a raiz da arvore binaria de busca
programa[30]: programa que esta sendo procurado
*/
void substituirAntecessor(Pasta *pasta);
/*
Acha o antecessor lexigrafico do programa e o troca de lugar com a pasta pedida
*pasta: ponteiro para a pasta que sera procurada o antecessor
*/
void testeVelocidade(int t_gasto, int t_max, char *prog);
/*
Testa se o programa esta sendo executado na velocidade desejada (tempo medido pelo nivel do programa)
t_gasto: tempo gasto (niveis percorridos) ate o programa ser aberto
t_max: tempo maximo permitido para o programa ser aberto
*prog: programa que sera testado
*/
int nivelPrograma(Pasta *raiz, char *busca, int nivel);
/*
Busca um programa especifico
*raiz: ponteiro para a raiz da arvore binaria de busca
*busca: string que esta sendo buscada
nivel: nivel atual da arvore binaria
*/
Pasta* balanceamento(Pasta *raiz);
/*
Cria uma arvore binaria de busca ordenada lexigraficamente nova e balanceada, a partir de uma antiga
*pasta: ponteiro para a raiz da arvore binaria
*/
void extraiSementeIn(Pasta *raiz, char **aux, int *indice);
/*
Extrai semente InOrdem de uma arvore binaria de busca. Utilizada para criar copias de segurança e criar arvores
*pasta: ponteiro para a raiz da arvore binaria de busca
**aux: vetor de strings em que sera guardada a semente
*indice: usado para o controle de indices na funcao
*/
void extraiSementePre(Pasta *raiz, char **aux, int *ind);
/*
Extrai semente de uma arvore binaria de busca ordenada lexicograficamente a partir de sua raiz
*raiz: ponteiro para a raiz da arvore binaria de busca
**aux: vetor de strings em que guardada a semente
*ind: usado para o controle de indices na funcao
*/
Pasta *criaArv(char **semente, int l, int r, Filho filho, Pasta *pai);
/*
Constroi uma arvore binaria de busca a partir de uma semente InOrdem criada pela funcao extraiSementeIn. Usado na hora de balancear uma arvore
l: numero do indice mais a esquerda que sera considerado
r: numero do indice mais a direita que sera considerado
*pai: ponteiro pro pai
filho: passa informacao se sera considerado i filho da esquerda ou da direita
*/
void criaCopia(Pasta *raiz, char **in, char **pre);
/*
Cria copia de seguranca da arvore atual retirando suas sementes InOrdem e PreOrdem
*raiz: ponteiro para a raiz da arvore binaria de busca
**In: vetor de strings em que guardada a semente InOrdem
**Pre: vetor de strings em que guardada a semente PreOrdem
*/
void imprime(Pasta *raiz);
/*
Imprime o diretorio de todos os programas salvos na arvore (C:/.../.../etc.exe) em ordem InOrdem
*raiz: ponteiro para a raiz da arvore binaria de busca
*/
void imprimeCaminho(Pasta *raiz, char *dire);
/*
Utilizada na funcao imprime. Concatena em uma string os nomes das pastas ate um programa que ainda nao foi visitado
*raiz: ponteiro para a raiz da arvore binaria de busca
*dire: string diretorio
*/
void desaloca(Pasta *raiz);
/*
Desaloca uma arvore inteira
*raiz: ponteiro para a raiz da arvore binaria de busca
*/

int  main() {
    int op, P, i, tempo, NUM_PROG_BACKUP;
    scanf("%d", &P);        //tamanho inicial da arvore
    Pasta *raiz;
    NUM_PROG = P;
    char **inOrdem, **preOrdem, programa[30];
    inOrdem = alocaMatriz(P, 30);
    preOrdem = alocaMatriz(P, 30);
    //salvando sementes iniciais
    for (i = 0; i < P; i++)
        scanf("%s", inOrdem[i]);
    for (i = 0; i < P; i++)
        scanf("%s", preOrdem[i]);
    int indPre = 0;
    NUM_PROG_BACKUP = NUM_PROG;
    raiz = constrArv(inOrdem, preOrdem, 0, P, &indPre, NULL, Raiz);     //construindo arvore inicial

    while (scanf("%d", &op) != EOF) {    //ate o arquivo acabar...

        switch (op) {
            case (1):
                scanf("%s", programa);
                raiz = inserir(raiz, programa);
                NUM_PROG++;
                break;

            case (2):
                scanf("%s", programa);
                if ((buscar(raiz, programa)) == NULL)   //se nao achar o programa
                    printf("[UNINSTALL] Nao foi encontrado no sistema nenhum programa com nome %s\n", programa);
                else{
                    raiz = remover(raiz, programa);     //se achar o programa
                    NUM_PROG--;
                    printf("[UNINSTALL] Programa %s.exe desinstalado com sucesso\n", programa);
                }
                break;

            case (3):
                scanf("%s %d", programa, &tempo);
                testeVelocidade(nivelPrograma(raiz, programa, 0), tempo, programa);
                break;

            case (4):
                raiz = balanceamento(raiz);
                break;

            case (5):
                inOrdem = alocaMatriz(NUM_PROG, 30);
                preOrdem = alocaMatriz(NUM_PROG, 30);
                NUM_PROG_BACKUP = NUM_PROG;
                criaCopia(raiz, inOrdem, preOrdem);
                break;

            case (6):
                indPre = 0;
                raiz = constrArv(inOrdem, preOrdem, 0, NUM_PROG_BACKUP, &indPre, NULL, Raiz);
                NUM_PROG = NUM_PROG_BACKUP;
                printf("[RESTORE] Sistema restaurado para a versao do backup\n");
                break;

            case (7):
                imprime(raiz);
                break;

            default:
                break;
        }
    }
    desaloca(raiz);     //liberando todo o espaço da memoria
}

Pasta* remover(Pasta *pasta, char programa[30]){
    if(pasta == NULL)       //pasta em NULL
        return NULL;
    if((strcmp(pasta->nome, "raiz")) == 0 && pasta->esq == NULL && pasta->dir == NULL){   //caso em que existe apenas a raiz sem filhos
        free(pasta);
        return NULL;
    }
    int teste = strcmp(programa, pasta->programa);
    if(teste<0){        //se a string programa e menor que o programa atual
        pasta->esq = remover(pasta->esq, programa);     //vai pro filho da esquerda
        if(pasta->esq != NULL){     //se tiver um filho esquerdo
            strcpy(pasta->esq->nome, pasta->programa);  //atualiza o nome de sua pasta
            strcat(pasta->esq->nome, "_esq");
        }
        return pasta;
    }else if(teste>0){      //analogo, porem para a direita
        pasta->dir = remover(pasta->dir, programa);
        if(pasta->dir != NULL){
            strcpy(pasta->dir->nome, pasta->programa);
            strcat(pasta->dir->nome, "_dir");
        }
        return pasta;
    }else if (pasta->esq == NULL){      //caso seja a string procurada e nao tem filho esquerdo
        Pasta *tmp = pasta->dir;
        if(strcmp(pasta->nome, "raiz")==0){
            strcpy(tmp->nome, pasta->nome);
        }
        free(pasta);//libera a memoria
        return tmp;
    }else if (pasta->dir == NULL){
        Pasta *tmp = pasta->esq;
        if(strcmp(pasta->nome, "raiz")==0){     //caso seja a string procurada e nao tem filho direito
            strcpy(tmp->nome, pasta->nome);
        }
        free(pasta);//libera a memoria
        return tmp;
    }else{        //caso seja a string procurada e tenha os dois filhos
        substituirAntecessor(pasta);    //acha o seu antecessor e substitui
        return pasta;
    }
}

void substituirAntecessor (Pasta *pasta){
    Pasta *pai = pasta, *t = pasta->esq;
    while(t->dir!=NULL){
        pai = t;
        t = t->dir;
    }   //t sera o antecessor do programa que sera removido
    //substitui o programa por seu antecessor e ajuda o nome das pastas dos filhos
    if(pai->esq == t){                  
        strcpy(pasta->dir->nome, t->programa);
        strcat(pasta->dir->nome, "_dir");
        pai->esq = t->dir;
    }
    else{
        strcpy(pasta->dir->nome, t->programa);
        strcat(pasta->dir->nome, "_dir");
        strcpy(pasta->esq->nome, t->programa);
        strcat(pasta->esq->nome, "_esq");
        pai->dir = t->esq;
    }
    strcpy(pasta->programa, t->programa);    
    free(t);    //libera a memoria
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

char **alocaMatriz(int lin, int col) {
    char **m = (char **) malloc(lin * sizeof(char *));
    for (int i = 0; i < lin; i++) {
        m[i] = (char *) malloc(col * sizeof(char));
        for (int j = 0; j < col; j++)
            m[i][j] = ' ';
    }
    return m;
}

Pasta *constrArv(char **inOrdem, char **preOrdem, int l, int r, int *indPre, Pasta *pai, Filho filho) {
    if (l < r) {    //enquanto left for maior que right...
        char prog[30];
        strcpy(prog, preOrdem[(*indPre)++]);        //salvando a raiz pela semente preOrdem
        int i = l;
        while (strcmp(prog, inOrdem[i]))        //procurando indice da raiz no inOrdem
            i++;
        Pasta *novo = malloc(sizeof(Pasta));
        strcpy(novo->programa, prog);
        novo->pai = pai;
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
    extraiSementeIn(raiz, aux, &indice);
    desaloca(raiz);
    raiz = criaArv(aux, 0, NUM_PROG-1, Raiz, NULL);
    printf("[OPTIMIZE] O sistema de acesso a programas foi otimizado\n");
    return raiz;
}
void extraiSementeIn(Pasta *raiz, char **aux, int *indice){
    if(raiz){
        extraiSementeIn(raiz->esq, aux, indice);
        strcpy(aux[(*indice)++], raiz->programa);
        extraiSementeIn(raiz->dir, aux, indice);
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
    extraiSementeIn(raiz, in, &indice1);
    extraiSementePre(raiz, pre, &indice2);
    printf("[BACKUP] Configuracao atual do sistema salva com sucesso\n");
}

void imprime(Pasta *raiz){
    char *diretorio = malloc(3*sizeof(char));
    strcpy(diretorio, "C:");
    printf("[PATHS]\n");
    imprimeCaminho(raiz, diretorio);
}

void imprimeCaminho(Pasta *raiz, char *dire) {
    if (raiz) {
        char *atual = malloc((strlen(dire) + 34) * sizeof(char));
        strcpy(atual, dire);
        strcat(atual, "/");
        strcat(atual, raiz->nome);
        imprimeCaminho(raiz->esq, atual);
        printf("%s/%s.exe\n", atual, raiz->programa);
        imprimeCaminho(raiz->dir, atual);
    }
}

    Pasta *buscar(Pasta *raiz, char programa[30]) {
        if (raiz == NULL || (strcmp(raiz->programa, programa)) == 0)
            return raiz;
        if ((strcmp(programa, raiz->programa)) < 0)
            return buscar(raiz->esq, programa);
        else
            return buscar(raiz->dir, programa);

    }
