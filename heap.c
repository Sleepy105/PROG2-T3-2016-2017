/*****************************************************************/
/*   Fila de prioridade / min-heap | PROG2 | MIEEC | 2016/17     */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ 			(0)
#define PAI(x) 			((x-1)/2)
#define FILHO_ESQ(x) 	((x*2)+1)
#define FILHO_DIR(x) 	((x*2)+2)

int menor_que(int e1, int e2);
int maior_que(int e1, int e2);

heap* heap_nova(int capacidade, int tipo_de_heap) {
	heap * h = (heap *) malloc(sizeof(heap));

	if (!h || (tipo_de_heap != MINHEAP && tipo_de_heap != MAXHEAP) )
		return NULL;

	h->tamanho = 0;
	h->capacidade = capacidade;
	h->elementos = (int*) calloc(capacidade, sizeof(int));
	h->tipo_de_heap = tipo_de_heap;

	if (!h->elementos) {
		free(h);
		return NULL;
	}

	return h;
}

void heap_apaga(heap *h) {
	if(!h)
		return;

	free(h->elementos);
	free(h);
}

int heap_insere(heap * h, int valor) {
	int aux, elem;
	int i;

	/* se heap esta' cheia, nao insere elemento */
	if (h->tamanho >= h->capacidade)
		return 0;

	/* coloca elemento no fim da heap */
	i = h->tamanho;
	h->elementos[i] = valor;
	h->tamanho++;

	if(h->tipo_de_heap == MINHEAP) {
		/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
		while (i != RAIZ && menor_que(h->elementos[i], h->elementos[PAI(i)])) {
			aux = h->elementos[PAI(i)];
			h->elementos[PAI(i)] = h->elementos[i];
			h->elementos[i] = aux;
			i = PAI(i);
		}
	}
	else if(h->tipo_de_heap == MAXHEAP) {
		/* enquanto elemento for menos prioritario do que o respetivo pai, troca-os */
		while (i != RAIZ && maior_que(h->elementos[i], h->elementos[PAI(i)])) {
			aux = h->elementos[PAI(i)];
			h->elementos[PAI(i)] = h->elementos[i];
			h->elementos[i] = aux;
			i = PAI(i);
		}
	}
	else
		return 0;
	
	return 1;
}

int heap_remove(heap * h) {
	int i, filho_maior, filho_menor, aux, ret;

	/* se heap estiver vazia, nao remove elemento */
	if (!h || h->tamanho <= 0)
		return -1;

	ret = h->elementos[RAIZ];

	/* coloca ultimo elemento da heap na raiz */
	h->tamanho--;
	h->elementos[RAIZ] = h->elementos[h->tamanho];
	h->elementos[h->tamanho] = 0;

	i = RAIZ;

	/* enquanto nao chegar 'a base da heap */
	while(FILHO_ESQ(i) < h->tamanho) {
		filho_maior = FILHO_ESQ(i);
		filho_menor = FILHO_DIR(i);

		/* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
		if (FILHO_DIR(i) < h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)])) {
			filho_maior = FILHO_DIR(i);
			filho_menor = FILHO_ESQ(i);
		}

		/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
		if(h->tipo_de_heap == MINHEAP) {
			if (menor_que(h->elementos[filho_maior], h->elementos[i])) {
				aux = h->elementos[filho_maior];
				h->elementos[filho_maior] = h->elementos[i];
				h->elementos[i] = aux;
				i = filho_maior;
			}
			else
				break;
		}
		else if(h->tipo_de_heap == MAXHEAP) {
			if (maior_que(h->elementos[filho_menor], h->elementos[i])) {
				aux = h->elementos[filho_menor];
				h->elementos[filho_menor] = h->elementos[i];
				h->elementos[i] = aux;
				i = filho_menor;
			}
			else
				break;
		}
		else
			return -1;
	}

	return ret;
}

void mostraHeap(heap *h, int indice) {
	int i, nivel = 0;

	if (indice < h->tamanho) {
		i = indice;
		while(i > RAIZ) {
			i = PAI(i);
			nivel++;
		}

		mostraHeap(h, FILHO_ESQ(indice));

		for(i = 0; i < 3 * nivel; i++)
			printf("     ");

		printf("%d\n", h->elementos[indice]);

		mostraHeap(h, FILHO_DIR(indice));
	}

	if (nivel == 0)
		printf("\n");
}

int menor_que(int e1, int e2) {

	return e1 < e2;
}

int maior_que(int e1, int e2) {

	return e1 > e2;
}
