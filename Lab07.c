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
  int tam;
}Pasta;

int inserir (Pasta *pasta, char programa[30]);

void alocar (Pasta *pasta, char programa[30], Filho filho);

void imprimeInOrdem(Pasta *pasta);

void inicializaRaiz(Pasta *raiz, int P);

int  main(){
  int op, P, i;
 
  scanf("%d", &P);
    
  Pasta *raiz = malloc(sizeof(Pasta));
  inicializaRaiz(raiz, P);
    
  char inOrdem[P][30], preOrdem[P][30], programa[30];
  
  for(i=0;i<P;i++)
    scanf("%s", inOrdem[i]);
  for(i=0;i<P;i++)
    scanf("%s", preOrdem[i]);
  
  while(scanf("%d", &op)!= EOF){    //ate o arquivo acabar...
    
    switch(op){     
      case(1):
        scanf("%s", programa);
        inserir(raiz, programa);    //raiz sera o no inicial que eu ainda nao criei nessa versao
        raiz->tam++;
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
void inicializaRaiz(Pasta *raiz, int P){
  raiz->programa[0] = 'r'; 
  raiz->tam = P;
  raiz->pai = NULL;
  raiz->dir = NULL;
  raiz->esq = NULL;
}
int inserir (Pasta *pasta, char programa[30]){
  if(pasta){
    if(pasta->tam == 0){
      Pasta *novo = malloc(sizeof(Pasta));  
      novo->dir = NULL;
      novo->esq = NULL;
      novo->pai = NULL;
      strcpy(novo->programa, programa);
      pasta = novo;
      return 1;
    }
    else{
      int teste = strcmp(programa, pasta->programa);
      if(teste<0){
        if(!inserir(pasta->esq, programa))
          alocar(pasta, programa, Esq);
        else
          inserir(pasta->esq, programa);
      }else{
        if(!inserir(pasta->dir, programa))
          alocar(pasta, programa, Esq);
        else
          inserir(pasta->dir, programa);
      }
      return 1;
    }
  }else{    
    return 0;
  }
}

void alocar (Pasta *pasta, char programa[30], Filho filho){
  Pasta *novo = malloc(sizeof(Pasta));  
  novo->dir = NULL;
  novo->esq = NULL;
  novo->pai = pasta;
  strcpy(novo->programa, programa);
  if(filho == Esq)
    pasta->esq = novo;
  else if(filho == Dir)
    pasta->dir = novo;  
}

void imprimeInOrdem(Pasta *pasta){
  if(pasta){
    imprimeInOrdem(pasta->esq);
    printf("Programa: %s\n", pasta->programa);
    imprimeInOrdem(pasta->dir);
  }
}

