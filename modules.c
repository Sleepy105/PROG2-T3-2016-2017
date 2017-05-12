#include "modules.h"
#include <stdio.h>
#include <string.h>
#include "tabdispersao.h"
#include "lista.h"

lista* list;
tabela_dispersao* td = NULL;
objeto* mode = NULL;

void median_initModule(int maxTransactions) {
  list = lista_nova();
}

int median_newObservation(int numActions, float *updatedMedian) {
  if( lista_insere(list, numActions) == NULL)
    return -1;
  
  int t = lista_tamanho(list);

  if(t == -1 || t == 0)
    return -1;
  else if (t % 2) {
    *updatedMedian = lista_meio(list)->valor;
    return 1;
  }
  else {
    l_elemento* meio = lista_meio(list);
    *updatedMedian = (float)(meio->valor + meio->proximo->valor) / 2;
    return 1;
  }
}

void median_closeModule() {
  lista_apaga(list);
}

void mode_initModule(int maxTransactions) {
  td = tabela_nova(maxTransactions/4, &hash_djbm);
}

int mode_newObservation(const char *companyName, char *updatedMode) {
  objeto* obj;

  if(tabela_insere(td, companyName, &obj) != TABDISPERSAO_OK)
    return -1;
  
  if(mode == NULL || obj->valor > mode->valor)
    mode = obj;
    
  strcpy(updatedMode, mode->chave);
  //printf("%s\n", updatedMode);
  return 1;
}

void mode_closeModule() {
  tabela_apaga(td);
  mode = NULL;
  td = NULL;
}
