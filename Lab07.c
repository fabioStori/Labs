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
}Pasta;

void inserir (Pasta *pasta, char programa[30], Filho filho);

void alocar (Pasta *pasta, char programa[30], Filho filho);

void imprimeInOrdem(Pasta *pasta);

void inicializaRaiz(Pasta *raiz);

int  main(){
  int op, P, i;
  Pasta *raiz = malloc(sizeof(Pasta));
  inicializaRaiz(raiz);
  scanf("%d", &P);
  
  char inOrdem[P][30], preOrdem[P][30], programa[30];
  
  for(i=0;i<P;i++)
    scanf("%s", inOrdem[i]);
  for(i=0;i<P;i++)
    scanf("%s", preOrdem[i]);
  
  while(scanf("%d", &op)!= EOF){    //ate o arquivo acabar...
    
    switch(op){     
      case(1):
        scanf("%s", programa);
        printf("2\n");
        inserir(raiz, programa, Raiz);    //raiz sera o no inicial que eu ainda nao criei nessa versao
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
  printf("\n");
  return 0;
}
void inicializaRaiz(Pasta *raiz){
  raiz->programa[0] = 'r'; raiz->programa[1] = '\n'; 
  raiz->pai = NULL;
  raiz->dir = NULL;
  raiz->esq = NULL;
}
void inserir (Pasta *pasta, char programa[30], Filho filho){
  if(pasta){
    int teste = strcmp(programa, pasta->programa);
    if(teste<0){
      inserir(pasta->esq, programa, Esq);
    }else{
      inserir(pasta->dir, programa, Dir);
    }
  }else{
    alocar(pasta, programa, filho);
  }
}

void alocar (Pasta *pasta, char programa[30], Filho filho){
  Pasta *novo = malloc(sizeof(Pasta));  
  novo->dir = NULL;
  novo->esq = NULL;
  novo->pai = pasta;
  strcpy(novo->programa, programa);
  printf("3\n");
  if(filho == Esq)
    pasta->esq = novo;
  else
    pasta->dir = novo;
  printf("4\n");
}
void imprimeInOrdem(Pasta *pasta){
  if(pasta){
    imprimeInOrdem(pasta->esq);
    printf("Programa: %s\n", pasta->programa);
    imprimeInOrdem(pasta->dir);
  }
}

