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

int  main(){
  int op, P, i;
 
  scanf("%d", &P);
    
  Pasta *raiz = NULL; //= malloc(sizeof(Pasta));
  //inicializaRaiz(raiz);
  //raiz = NULL;
    
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
void inicializaRaiz(Pasta *raiz){
  raiz->pai = NULL;
  raiz->dir = NULL;
  raiz->esq = NULL;
}
Pasta* inserir (Pasta *pasta, char programa[30]){
  printf("asdf\n");
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
    printf("aos\n");
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
  strcpy(novo->nome, programa);
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
