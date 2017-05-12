/*****************************************************************/
/*      Biblioteca lista ligada | PROG2 | MIEEC | 2016/17        */
/*****************************************************************/

#include "lista.h"
#include <string.h>
#include <stdlib.h>

l_elemento* novo_elemento(int valor) {
	/* aloca memoria para a estrutura lista */
	l_elemento *item = (l_elemento *) malloc(sizeof(l_elemento));
	if(item == NULL)
		return NULL;

	/* copia valor */
	item->valor = valor;

	/* item ainda nao tem proximo */
	item->proximo = NULL;
	item->anterior = NULL;

	return item;
}

lista* lista_nova() {
	/* cria lista */
	lista *lst = (lista*) malloc(sizeof(lista));
	if(lst == NULL)
		return NULL;

	/* lista esta' vazia */
	lst->inicio = NULL;
	lst->meio = NULL;
	lst->fim = NULL;
	lst->tamanho = 0;

  return lst;
}

void lista_apaga(lista *lst) {
	l_elemento *aux;

	if(lst == NULL)
		return;

	/* percorre toda a lista e liberta memoria de
	   cada item e respectiva string */
	while(lst->inicio) {
		aux = lst->inicio;
		lst->inicio = lst->inicio->proximo;
		free(aux);
	}

	free(lst);
	return;
}

int lista_tamanho(lista *lst) {
	if(lst == NULL)
		return -1;
	return lst->tamanho;
}

l_elemento* lista_meio(lista* lst) {
	if(lst == NULL)
		return NULL;
	
	return lst->meio;
}

l_elemento* lista_elemento(lista *lst, int pos) {
	int i;
	l_elemento *curr = NULL;

	if (lst == NULL || pos < 0 || pos >= lst->tamanho)
		return NULL;

	curr = lst->inicio;
	for(i=0; i<pos; i++)
		curr = curr->proximo;

	return curr;
}

l_elemento* sniffer(lista* lst, int valor) {
	if(lst == NULL)
		return NULL;
	
	l_elemento* aux;
	
	if(valor <= lst->meio->valor) {
		for(aux = lst->meio; aux->anterior != NULL; aux = aux->anterior) {
			if(aux->valor <= valor)
				break;
		}
		return aux;
	}
	/*else if(valor >= lst->fim->valor) {
		return lst->fim;
	}*/
	else {
		for(aux = lst->meio; aux->proximo != NULL; aux = aux->proximo) {
			if(aux->proximo->valor >= valor)
				break;
		}
		return aux;
	}

	return NULL;
}

l_elemento* lista_insere(lista *lst, int valor) {
	if (lst == NULL)
		return NULL;

	/* cria novo item */
	l_elemento* curr = novo_elemento(valor);

	if (curr == NULL)
        return NULL;

	lst->tamanho++;

	curr->valor = valor;

	l_elemento* aux;

	/* se e' primeiro l_elemento */
	if (lst->inicio == NULL) {
		lst->inicio = lst->meio = lst->fim = curr;
		return curr;
	}
	else {
		/* Se deve ser inserido no início da lista */
		if(lst->inicio->valor > valor){
			lst->inicio->anterior = curr;
			curr->proximo = lst->inicio;
			lst->inicio = curr;
		}
		else {
			aux = sniffer(lst, valor);
			if(aux == NULL)
				return NULL;

			/* Se deve ser inserido no fim da lista */
			if(aux == lst->fim) {
				curr->anterior = lst->fim;
				lst->fim->proximo = curr;
				lst->fim = curr;
			}
			else { /* Caso deva ser inserido em qualquer posição intermediária */
				curr->proximo = aux->proximo;
				curr->anterior = aux;
				aux->proximo->anterior = curr;
				aux->proximo = curr;
			}
		}
	}

	if( !(lst->tamanho % 2) && valor < lst->meio->valor)
		lst->meio = lst->meio->anterior;
	else if( (lst->tamanho % 2) && valor >= lst->meio->valor)
		lst->meio = lst->meio->proximo;
	/*aux = lst->inicio;
	for(int i = 0; i < (lst->tamanho - 1) / 2; i++)
		aux = aux->proximo;
	lst->meio = aux;*/

	return curr;
}

l_elemento* lista_remove(lista *lst, l_elemento *pos) {
	l_elemento *aux;

	if (lst == NULL || pos == NULL)
		return NULL;

	lst->tamanho--;

	/* troca apontadores para remover item */
	if(pos->anterior != NULL)
		pos->anterior->proximo = pos->proximo;
	else /* e' o primeiro */
		lst->inicio = pos->proximo;
	if(pos->proximo != NULL)
		pos->proximo->anterior = pos->anterior;
	else /* e' o ultimo */
		lst->fim = pos->anterior;

	/* liberta memoria associada ao item removido */
	aux = pos->proximo;
	free(pos);

	return aux;
}

int lista_atribui(lista *lst, l_elemento *pos, int valor) {
	if(lst == NULL || pos == NULL)
		return -1;

	pos->valor = valor;

	return 0;
}

l_elemento* lista_pesquisa(lista *lst, int valor, int origem) {
	l_elemento *aux;

	if(lst == NULL || (origem != LISTA_INICIO && origem != LISTA_FIM))
		return NULL;

	if(origem == LISTA_INICIO)
	{
		/* pesquisa sequencial: a partir do inicio */
		for (aux = lst->inicio; aux != NULL; aux = aux->proximo)
		{
			if (aux->valor == valor)
				return aux;
		}
		return NULL;
	}

	/* pesquisa sequencial: a partir do fim */
	for (aux = lst->fim; aux != NULL; aux = aux->anterior)
	{
		if (aux->valor == valor)
			return aux;
	}
	return NULL;
}

int lista_ordena(lista *lst) {
    l_elemento *next, *curr, *min;
    int aux;

	if(lst == NULL)
		return -1;

	/* lista vazia ja' esta' ordenada */
	if(lst->tamanho == 0)
		return 0;

	/* algoritmo de ordenacao por seleccao */
    for(curr = lst->inicio; curr->proximo != NULL; curr=curr->proximo)
    {
		min = curr;
		next = curr->proximo;
		while(next != NULL)
		{
            if(next->valor < min->valor)
            	min = next;
            next = next->proximo;
		}
		/* basta trocar strings */
		if (min != curr)
		{
            aux = curr->valor;
	    	curr->valor = min->valor;
	    	min->valor = aux;
		}
    }

	return 0;
}
