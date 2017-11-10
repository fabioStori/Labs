/*
  Lab07: Painel de Controle de Programas
  Nome: Fabio Stori
  RA: 196631
  Nome: Adivair Satan Ramos
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

Pasta* remover(Pasta *pasta, char programa[30]);

void substituirAntecessor(Pasta *pasta);


int  main(){
  int op, P, i;
 
  scanf("%d", &P);
    
  Pasta *raiz = NULL;
  
  char inOrdem[P][30], preOrdem[P][30], programa[30];
  
  for(i=0;i<P;i++)
    scanf("%s", inOrdem[i]);
  for(i=0;i<P;i++)
    scanf("%s", preOrdem[i]);
  
  while(scanf("%d", &op)!= EOF){    //ate o arquivo acabar...
    
    switch(op){     
      case(1):
        scanf("%s", programa);
        raiz = inserir(raiz, programa);
        printf("Programa: %s | Pasta: %s\n", raiz->programa, raiz->nome);
      break;        
      case(2):
        scanf("%s", programa);
        raiz = remover(raiz, programa);
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
    return pasta;
  }else if(teste>0){
    pasta->dir = remover(pasta->dir, programa);
    return pasta;      
  }else if (pasta->esq == NULL){
    return pasta->dir;
  }else if (pasta->dir == NULL){
    return pasta->esq;
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
  //free(t);
  printf("Programa: %s, Pasta: %s | removidos\n", pasta->programa, pasta->nome);
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

