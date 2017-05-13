#include "modules.h"
#include <stdio.h>
#include <string.h>
#include "tabdispersao.h"
#include "heap.h"

#define ERROR -1
#define ALL_GOOD  1

heap *min, *max;

tabela_dispersao* td = NULL;
objeto* mode = NULL;

void median_initModule(int maxTransactions) {
  min = heap_nova(maxTransactions/2 + 1, MINHEAP);
  max = heap_nova(maxTransactions/2, MAXHEAP);
}

int median_newObservation(int numActions, float *updatedMedian) {
  if(!heap_insere(max, numActions, numActions))
    return ERROR;

  if(max->tamanho - min->tamanho > 1) {
    int aux = heap_remove(max);
    if(aux == -1)
      return ERROR;
    
    if(!heap_insere(min, aux, aux))
      return ERROR;
  }

  if(min->elementos[0] != NULL && max->elementos[0]->valor > min->elementos[0]->valor) {
    int aux = heap_remove(max);
    int aux2 = heap_remove(min);
    
    if(!heap_insere(min, aux, aux))
      return ERROR;
    if(!heap_insere(max, aux2, aux2))
      return ERROR;
  }

  if( (max->tamanho + min->tamanho) % 2 )
    *updatedMedian = max->elementos[0]->valor;
  else
    *updatedMedian = (float)(max->elementos[0]->valor + min->elementos[0]->valor) / 2;
  
  /*mostraHeap(max, 0);
  printf("______________________\n");
  mostraHeap(min, 0);
  printf("pppppppppppppppppppppp\n");*/

  return ALL_GOOD;
}

void median_closeModule() {
  heap_apaga(min);
  heap_apaga(max);
}

void mode_initModule(int maxTransactions) {
  td = tabela_nova(maxTransactions/3, &hash_djbm);
}

int mode_newObservation(const char *companyName, char *updatedMode) {
  objeto* obj;

  if(tabela_insere(td, companyName, &obj) != TABDISPERSAO_OK)
    return ERROR;
  
  if(mode == NULL || obj->valor > mode->valor)
    mode = obj;
    
  strcpy(updatedMode, mode->chave);
  //printf("%s\n", updatedMode);
  return ALL_GOOD;
}

void mode_closeModule() {
  tabela_apaga(td);
  mode = NULL;
  td = NULL;
}
