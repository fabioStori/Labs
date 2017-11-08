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

typedef struct Pasta{
  struct Pasta *dir;
  struct Pasta *esq;
  struct Pasta *pai;
  char programa[30];
}Pasta;

void inserir (Pasta *pasta, char programa[30]);

void alocar (Pasta *pasta, char programa[30]);

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
        inserir(raiz, programa);    //raiz sera o no inicial que eu ainda nao criei nessa versao
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
void inserir (Pasta *pasta, char programa[30]){
  if(pasta){
    printf("3\n");
    int teste = strcmp(programa, pasta->programa);
    printf("3\n");
    if(teste<0){
      printf("3\n");      
      inserir(pasta->esq, programa);
      printf("3\n");
    }else{
      printf("4\n");
      inserir(pasta->dir, programa);
      printf("4\n");
    }
  }else{
    printf("5\n");
    alocar(pasta, programa);
    printf("5\n");
  }
}

void alocar (Pasta *pasta, char programa[30]){
  Pasta *novo = malloc(sizeof(Pasta));
  novo->pai = pasta;
  strcpy(novo->programa, programa);
  novo->dir = NULL;
  novo->esq = NULL;
}
void imprimeInOrdem(Pasta *pasta){
  if(pasta){
    imprimeInOrdem(pasta->esq);
    printf("Programa: %s\n", pasta->programa);
    imprimeInOrdem(pasta->dir);
  }
}

