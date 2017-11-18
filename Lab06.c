/*
  Lab06: Gerenciador de Memória
  Nome: Fabio Stori
  RA: 196631
  Nome: Adivair Santana Ramos
  RA: 193325
  Turma E - MC202
*/
#include<stdlib.h>
#include<stdio.h>

typedef enum {Livre, Ocupado, Particionado} Estado;

typedef struct No{
  int cod;
  int size;
  int size_max;
  struct No* pai;
  struct No* esq;
  struct No* dir;
  Estado estado;
}No;

void inicializa_Raiz(No *raiz, int exp);

int inserir_no(No *arvore, int cod, int size, int exp);
//percorre em pre-ordem ate encontrar um no livre e com espaço suficiente, insere ou cria dois filhos

void criarFilhos(No *arvore, int exp);
//dado um No, cria dois filhos com espaço 2^exp;

int remover (No *arvore, int cod);
//remove um no especifico dado o Cod;

void removerPai(No *arvore);

void calcula_Frag(No *arvore, int *frag);
//percorre toda arvore somando em uma acumuladora o valor de memoria desperdiçada

int imprimeOcupados(No *arvore, int i);
//imprime os Nos folhas ocupados

void relatorio(No *arvore);
//percorre a arvore recursivamente, acumulando os valores de memoria usados e a quantidade de cada tipo de Nós

void calcula_Inf(No *arvore, int *p, int *o, int *l, int *u);
//função de percorrer usada em relatorio

void imprime_Sem(No *arvore);
//imprime os Nós dado o percurso(in, pre, pos ordem)
void imprime_Sim(No *arvore);

void imprime_Pre(No *arvore);

void imprime_Pos(No *arvore);

int pot_2(int exp);

void desalocar(No *arvore);

int  main(){
  int exp, op, cod, size, teste, frag;
  
  scanf("%d", &exp);    
  No *raiz = malloc(sizeof(No));
  inicializa_Raiz(raiz, exp);
  
  while(scanf("%d", &op)!= EOF){    //ate o arquivo acabar...
    
    switch(op){
      
    case(1):
      scanf("%d %d", &cod, &size);
      teste = inserir_no(raiz, cod, size, exp);
      if(!teste)
        printf("Memoria insuficiente\n");
      break;
      
    case(2):
      scanf("%d", &cod);
      if(remover(raiz, cod))
	printf("Processo (%d) finalizado com sucesso\n", cod);
      else
	printf("Nao existe processo de codigo %d inicializado no sistema\n", cod);
      break;
      
    case(3): 
      frag = 0;        
      calcula_Frag(raiz, &frag);
      printf("Quantidade total de memoria desperdicada por fragmentacao: %d\n", frag);
      break;
      
    case(4):             
      relatorio(raiz);
      break;
      
    case(5):
      imprime_Sem(raiz);
      break;
    case(6):
      printf("[PROCESSOS PRESENTES NA MEMORIA]\n");
      teste = imprimeOcupados(raiz, 1);
    if(teste)
      printf("Nenhum processo presente\n");
    break;
    }
  }
  printf("\n");
  desalocar(raiz);
  //free(raiz);
  return 0;
}


void inicializa_Raiz(No *raiz, int exp){ //Inicicializa a raiz como um no livre, sem pai e filhos...
  raiz->pai = NULL;
  raiz->esq = NULL;
  raiz->dir = NULL;
  raiz->estado = Livre;
  raiz->size = 0;
  raiz->size_max = pot_2(exp); 
}

int inserir_no(No *arvore, int cod, int size, int exp){
  if(arvore){
    if((arvore->estado == Livre) && (size <= arvore->size_max)){// Se encontrar um livre que cabe, verifica as condiçoes de inserção ou fragmentação
      if((size > arvore->size_max/2)){// Se o valor for maior que a metade do No, ocupa-o
	arvore->cod = cod;
	arvore->size = size;
	arvore->estado = Ocupado;
	printf("Processo (%d) de tamanho %d inicializado com sucesso\n", cod, size);
	return 1;
      }else{// Se o valor for menor que a metade do No, fragmenta-o
	arvore->estado = Particionado;
	criarFilhos(arvore, exp-1);                
      }
    }   
    if(inserir_no(arvore->esq, cod, size, exp-1))
      return  1;        
    return inserir_no(arvore->dir, cod, size, exp-1);              
  }
  return 0;
}


void criarFilhos(No *arvore, int exp){
  No *novo_1, *novo_2;
  novo_1 = malloc(sizeof(No));
  novo_2 = malloc(sizeof(No));
  
  novo_1->esq = NULL;             novo_2->esq = NULL;  
  novo_1->dir = NULL;             novo_2->dir = NULL;
  novo_1->pai = arvore;           novo_2->pai = arvore;
  novo_1->size_max = pot_2(exp);   novo_2->size_max = pot_2(exp);
  novo_1->estado = Livre;         novo_2->estado = Livre;
  
  arvore->esq = novo_1;           arvore->dir = novo_2;
}

int pot_2(int exp){
  int total=1, i;
  for(i=0; i < exp; i++)  
    total = total*2;
  return total;
}

int remover (No *arvore, int cod){
  if(arvore){
    if((arvore->estado == Ocupado) && (arvore->cod == cod)){
            arvore->estado = Livre;
            arvore->cod = 0;
            arvore->size = 0;
            return 1;
    }
    int teste = remover(arvore->esq, cod);
    if(teste){
      if((arvore->esq->estado == Livre) && (arvore->dir->estado == Livre)){
	removerPai(arvore);
      }
      return 1;
    }
    teste = remover (arvore->dir, cod);
        if(teste){
	  if((arvore->esq->estado == Livre) && (arvore->dir->estado == Livre)){
	    removerPai(arvore);
	  }
	  return 1;
        }
        return 0;
  }
  return 0;
}

void removerPai(No *arvore){
  arvore->estado = Livre;
  arvore->cod = 0;
  arvore->size = 0;
  free(arvore->esq);
  free(arvore->dir);
  arvore->esq = NULL;
  arvore->dir = NULL;
}

void calcula_Frag(No *arvore, int *frag){  
  if(arvore){
    if(arvore->estado == Ocupado){
      (*frag) = (*frag) + (arvore->size_max - arvore->size);
    }
    calcula_Frag(arvore->esq, frag);
    calcula_Frag(arvore->dir, frag);
  }
}
int imprimeOcupados(No *arvore, int i){
  if(arvore){        
    i= imprimeOcupados(arvore->esq, i);
    if(arvore->estado == Ocupado){
      printf("%d [Processo: %d]\n", arvore->size_max, arvore->cod);
      i=0;
    }
    i = imprimeOcupados(arvore->dir, i);
  }
  return i;
}


void calcula_Inf(No *arvore, int *p, int *o, int *l, int *u){
  if(arvore){
    if(arvore->estado == Ocupado){
      (*o)++;
      (*u) = (*u) + arvore->size_max;
    }      
    if(arvore->estado == Particionado)
      (*p)++;
    if(arvore->estado == Livre)
      (*l)++;
    calcula_Inf(arvore->esq, p, o, l, u);
    calcula_Inf(arvore->dir, p, o, l, u);
  }
}

void relatorio(No *arvore){
  int p=0, o=0, l=0, u=0, max= arvore->size_max;
  float por;  
  printf("[RELATORIO DE SISTEMA]\n");
  calcula_Inf(arvore, &p, &o, &l, &u);
  por = (float) u / (float) (max)*100;
  printf("%d Ocupados\n%d Livres\n%d Particionados\nMemoria utilizada = %d / 100\n", o, l, p, (int) por);
}


void imprime_Sem(No *arvore){
  printf("[SEMENTES GERADORAS]\n");
  printf("Sim = "); imprime_Sim(arvore); printf("\n");
  printf("Pre = "); imprime_Pre(arvore); printf("\n");
  printf("Pos = "); imprime_Pos(arvore); printf("\n");
  
}

void imprime_Sim(No *arvore){
  if(arvore){
    imprime_Sim(arvore->esq);
    if(arvore->estado == Livre)
        printf("(L:%d)", arvore->size_max);
    else if(arvore->estado == Particionado)
      printf("(P:%d)", arvore->size_max);
    else
      printf("(O:%d/%d[%d])", arvore->size, arvore->size_max, arvore->cod);   
    imprime_Sim(arvore->dir);
  }
}


void imprime_Pre(No *arvore){
  if(arvore){
    if(arvore->estado == Livre)
      printf("(L:%d)", arvore->size_max);
    else if(arvore->estado == Particionado)
      printf("(P:%d)", arvore->size_max);
      else
	printf("(O:%d/%d[%d])", arvore->size, arvore->size_max, arvore->cod);   
    imprime_Pre(arvore->esq);
    imprime_Pre(arvore->dir);
  }
}



void imprime_Pos(No *arvore){
  if(arvore){
    imprime_Pos(arvore->esq);
    imprime_Pos(arvore->dir);
    if(arvore->estado == Livre)
      printf("(L:%d)", arvore->size_max);
    else if(arvore->estado == Particionado)
      printf("(P:%d)", arvore->size_max);
      else
	printf("(O:%d/%d[%d])", arvore->size, arvore->size_max, arvore->cod);  
    
  }
}

void desalocar(No *arvore){  
  if(arvore){
    desalocar(arvore->esq);
    desalocar(arvore->dir);
    free(arvore);
  }
}  
