#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* descricao do elemento da fila */
struct fila_nodo_t {
	int item;
	struct fila_nodo_t *prox; /* ponteiro para o proximo */ 
};

struct fila_t {
	struct fila_nodo_t *ini; /* primeiro elemento */
	struct fila_nodo_t *ult; /* ultimo elemento */
	int num; /* quantidade de elementos */
};

/* cria uma fila sem nada */
struct fila_t *fila_cria() {
	struct fila_t *fila_vazia = malloc(sizeof(struct fila_t));
	if (!fila_vazia)
		return NULL;
	fila_vazia->ini = NULL;
	fila_vazia->ult = NULL;
	fila_vazia->tam = 0;
	return fila_vazia;
};

/* retorna uma fila vazia, com todos os elementos e estruturas destruidos */
struct fila_t *fila_destroi(struct fila_t *f) {
	if (f == NULL){
		return NULL;
	}
	struct fila_nodo_t *aux_atual = f->ini;
	struct fila_nodo_t *aux_prox;
	while (aux_atual != NULL){
		aux_prox = aux_atual->prox;
		free(aux_atual);
		aux_atual = aux_prox;
		(f->num)--;
	}
	free(f);
	f = NULL;
	return NULL;
};

/* insere um elemento no fim da fila */
int fila_insere(struct fila_t *f, int item){
	struct fila_nodo_t *nodo = malloc(sizeof(struct fila_nodo_t);
	if (!(f) || !(nodo))
		return 0;
	nodo->item = item;
	nodo->prox = NULL;
	if (f->num == 0)
		f->ini = nodo
	else
		f->ult->prox = nodo;
	f->num++;
	return 1;
}

/* retira um elemento do fim da fila, por ordem de chegada */
int fila_retira(struct fila_t *f, int *item){
	if (!(f) || !(item) || f->num == 0)
		return 0;
	*item = f->ini->item;
	struct fila_nodo_t *aux = f->ini;
       	f->ini = aux->prox;
	free(aux);
	f->num--;

	if (f->prim == NULL)
		f->ult == NULL;
	return 1;
}

/* retorna o tamanho da fila */
int fila_tamanho(struct fila_t *f){
	if (f == NULL)
		return -1;
	return f->num;
}

/* imprime todos os elementos da fila */
void fila_imprime(struct fila_t *f){
	if (f == NULL || f->num == 0)
		return;
	struct fila_nodo_t *aux = f->ini;
	while (aux->prox != NULL){
		printf("%d ", aux->item);
		aux = aux->prox;
	}
	printf("%d", aux->item);
}
