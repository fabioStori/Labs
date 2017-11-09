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

void remover (Pasta *pasta, char programa[30], Filho filho);

void removerFolha(Pasta *pasta, Filho filho);

void remover1Filho(Pasta *pasta, Filho filho);

void remover2Filhos(Pasta *pasta, Filho filho);

void mudaNome(Pasta *pasta, Filho filho);

Pasta* antecessor(Pasta *pasta);

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
        printf("Programa: %s | Pasta: %s\n", raiz->programa, raiz->nome);
      break;        
      case(2):
        scanf("%s", programa);
        remover(raiz, programa, Raiz);
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
/*void inicializaRaiz(Pasta *raiz){
  raiz->pai = NULL;
  raiz->dir = NULL;
  raiz->esq = NULL;
}*/

void remover (Pasta *pasta, char programa[30], Filho filho){
  if(pasta){    //se nao for nulo
    int teste = strcmp(programa, pasta->programa);    //testa se o programa e maior ou menor
    if(teste==0){ //achou o programa
      if(pasta->esq == NULL && pasta->dir == NULL){   //caso em que e uma folha
        printf("achou folha\n");
        removerFolha(pasta, filho);
      }else if(pasta->esq != NULL && pasta->dir == NULL || pasta->esq == NULL && pasta->dir != NULL){   //caso em que existe apenas 1 filho
        remover1Filho(pasta, filho);
      }else{    //caso com 2 filhos
        remover2Filhos(pasta, filho);
      }
    }else if(teste<0){      //se for menor, vai pra esquerda
      remover(pasta->esq, programa, Esq);
    }else{      //se nao for menor, é maior, logo executa um procedimento analogo para a direita
      remover(pasta->dir, programa, Dir);
    }    
  }
}

void removerFolha(Pasta *pasta, Filho filho){
  if(filho == Esq){     //caso a pasta com o programa seja um filho da esquerda
    pasta->pai->esq = NULL;   //a esquerda do pai sera liberada
    free(pasta);
  }else{
    pasta->pai->dir = NULL;   //se nao, sera a direita do pai que sera liberada
    free(pasta);
  }
}

void remover1Filho(Pasta *pasta, Filho filho){
  if(filho == Esq){   //caso a pasta com o programa seja um filho da esquerda
    if(pasta->esq){   //e o filho da esquerda dessa pasta (que será removida) nao seja nulo
      mudaNome(pasta, Esq);                                                                  //apenas corrigindo o nome da pasta, que agora tera um novo pai
      pasta->pai->esq = pasta->esq;     //a esquerda do pai apontará pro filho da esquerda
      free(pasta);
    }else{    //se nao, apontara pro filho da direita (pois o esquerdo sera o nulo, e o direito o nao nulo)
      mudaNome(pasta, Dir);    //e o resto e analogo ao caso anterior
      pasta->pai->esq = pasta->dir;   
      free(pasta);
    }
  }else{    //se nao, sera um filho da direita
    if(pasta->esq){     //e o resto e analogo ao da esquerda
      mudaNome(pasta, Esq);
      pasta->pai->dir = pasta->esq;
      free(pasta);
    }else{
      mudaNome(pasta, Dir);
      pasta->pai->dir = pasta->dir;
      free(pasta);
    }
  }
}

void mudaNome(Pasta *pasta, Filho filho){
  if(filho == Esq){
    strcpy(pasta->esq->nome, pasta->programa);    
    strcat(pasta->esq->nome, "_esq");
  }else{
    strcpy(pasta->dir->nome, pasta->programa);    
    strcat(pasta->dir->nome, "_dir");
  }
}

void remover2Filhos(Pasta *pasta, Filho filho){
  if(filho == Esq){
    pasta->pai->esq = antecessor(pasta);
    free(pasta);
  }else{
    pasta->pai->dir = antecessor(pasta);;
    free(pasta);
  }
}

Pasta* antecessor(Pasta *pasta){
  Pasta *tmp = pasta->esq;
  while(tmp->esq!=NULL){
    tmp = tmp->esq;
  }
  return tmp;
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

