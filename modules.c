#include "modules.h"
#include <stdio.h>
#include <string.h>
#include "tabdispersao.h"
#include "heap.h"

#define ERROR -1
#define ALL_GOOD  1

heap *min, *max;
float m;

tabela_dispersao* td = NULL;
td_elemento* mode = NULL;

void median_initModule(int maxTransactions) {
    min = heap_nova(maxTransactions/2 + 1, MINHEAP);
    max = heap_nova(maxTransactions/2, MAXHEAP);
    m = 0;
}

int median_newObservation(int numActions, float *updatedMedian) {
    if(max == NULL || min == NULL)
        return ERROR;

    switch(max->tamanho - min->tamanho) {
        case 1: // Left-heavy

            if(numActions < m) {
                int aux = heap_remove(max);
                if(aux == -1)
                    return ERROR;
                
                if(!heap_insere(min, aux))
                    return ERROR;
                
                if(!heap_insere(max, numActions))
                    return ERROR;
            }
            else {
                if(!heap_insere(min, numActions))
                    return ERROR;
            }

            // Agora ambas as heaps têm o mesmo número de elementos
            m = *updatedMedian = (float)(max->elementos[0] + min->elementos[0]) / 2;

            break;

        case 0: // Balanced

            if(numActions < m) {
                if(!heap_insere(max, numActions))
                    return ERROR;
                m = *updatedMedian = (float)(max->elementos[0]);
            }
            else {
                if(!heap_insere(min, numActions))
                    return ERROR;
                m = *updatedMedian = (float)(min->elementos[0]);
            }

            break;

        case -1: // Right-heavy

            if(numActions < m) {
                if(!heap_insere(max, numActions))
                    return ERROR;
            }
            else {
                int aux = heap_remove(min);
                if(aux == -1)
                    return ERROR;
                
                if(!heap_insere(max, aux))
                    return ERROR;
                
                if(!heap_insere(min, numActions))
                    return ERROR;
            }

            m = *updatedMedian = (float)(max->elementos[0] + min->elementos[0]) / 2;

            break;
    }

    /* Determina mediana 
    if( (max->tamanho + min->tamanho) % 2 )
        m = *updatedMedian = max->elementos[0]->valor;
    else
        m = *updatedMedian = (float)(max->elementos[0]->valor + min->elementos[0]->valor) / 2;*/
  
    /*mostraHeap(max, 0);
    printf("______________________\n");
    mostraHeap(min, 0);
    printf("pppppppppppppppppppppp\n");*/

    return ALL_GOOD;
}

void median_closeModule() {
    heap_apaga(min);
    heap_apaga(max);
    m = 0;
}

void mode_initModule(int maxTransactions) {
    td = tabela_nova(maxTransactions, &hash_djb2m);
}

int mode_newObservation(const char *companyName, char *updatedMode) {
    td_elemento* elem;

    if(mode != NULL && strcmp(mode->chave, companyName) == 0) {
        (mode->valor)++;
        
        strcpy(updatedMode, mode->chave);
        return ALL_GOOD;
    }
    else if(tabela_insere(td, companyName, &elem) != TABDISPERSAO_OK)
        return ERROR;
  
    if(mode == NULL || elem->valor > mode->valor)
        mode = elem;
    
    strcpy(updatedMode, mode->chave);
    return ALL_GOOD;
}

void mode_closeModule() {
    tabela_apaga(td);
    mode = NULL;
    td = NULL;
}
