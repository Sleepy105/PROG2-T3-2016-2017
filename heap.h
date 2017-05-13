/*****************************************************************/
/*   Fila de prioridade / min-heap | PROG2 | MIEEC | 2016/17     */
/*****************************************************************/

#ifndef HEAP_H
#define HEAP_H

#define MINHEAP 0
#define MAXHEAP 1

typedef struct {
	int prioridade;
	int valor;
} elemento;

typedef struct {
	/* numero de elementos no vetor */
	int tamanho;
	/* tamanho maximo do vetor */
	int capacidade;

	/* vetor de apontadores para elementos */
	elemento ** elementos;

	/* tipo de heap */
	int tipo_de_heap;
} heap;

/* cria nova heap */
heap* heap_nova(int tamanho_maximo, int tipo_de_heap);

/* apaga heap */
void heap_apaga(heap *h);

/* insere elemento na heap com uma determinada prioridade */
int heap_insere(heap *h, int valor, int prioridade);

/* remove elemento na raiz da heap */
int heap_remove(heap *h);

/* imprime o estado actual da heap, a partir do indice indicado */
void mostraHeap(heap *h, int indice);

#endif /* HEAP_H */
