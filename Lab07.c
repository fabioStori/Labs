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

typedef struct No{

}No;

int  main(){
  int op, P, i;
  
  scanf("%d", &P);
  
  char in-ordem[P][30], pre-ordem[P][30];
  
  for(i=0;i<P;i++)
    scanf("%s", in-ordem[i]);
  for(i=0;i<P;i++)
    scanf("%s", pre-ordem[i]);
  
  while(scanf("%d", &op)!= EOF){    //ate o arquivo acabar...
    
    switch(op){     
      case(1):
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
      break;
    }
  }
  printf("\n");
  return 0;
}

