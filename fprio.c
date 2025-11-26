// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

/* cria uma fila vazia */
struct fprio_t *fprio_cria (){
	struct fprio_t *novafila = malloc(sizeof(struct fprio_t));
	if (!novafila)
		return NULL;
	novafila->num = 0;
	novafila->prim = NULL;
	return novafila;
};

/* destroi todos os nodos da fila de prioridade e a libera */
struct fprio_t *fprio_destroi (struct fprio_t *f){
	if (f != NULL){
		struct fpnodo_t *aux_atual = f->prim;
		struct fpnodo_t *aux_prox;
		while (aux_atual != NULL){
			aux_prox = aux_atual->prox;
			free(aux_atual);
			aux_atual = aux_prox;
		}
		free(f);
		f = NULL;
	}
	return NULL;
}

/* coloca o item na fila e mantem a ordenaçao por prioridades crescentes. */
/* se houver itens com a mesma prioridade, o que estiver la ha mais tempo */
/* sai por primeiro. */
/* inserir duas vezes o mesmo item (o mesmo ponteiro) eh um erro. */
/* retornar a quantidade de itens na fila depois da operação ou -1 se erro */
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
    if (f == NULL || item == NULL)
        return -1;

/* verifica se n esta duplicado */
    struct fpnodo_t *tmp = f->prim;
    while (tmp) {
        if (tmp->item == item)
            return -1;
        tmp = tmp->prox;
    }

    struct fpnodo_t *novo = malloc(sizeof(struct fpnodo_t));
    if (!novo)
        return -1;

    novo->item = item;
    novo->tipo = tipo;
    novo->prio = prio;
    novo->prox = NULL;

    struct fpnodo_t *ant = NULL;
    struct fpnodo_t *atual = f->prim;

/* percorre enquanto tiver prioridade igual ou menor */ 
    while (atual && atual->prio <= prio) {
        ant = atual;
        atual = atual->prox;
    }

    if (ant == NULL) {
        novo->prox = f->prim;
        f->prim = novo;
    } else {
        novo->prox = atual;
        ant->prox = novo;
    }

    f->num++;
    return f->num;
}


/* retira o primeiro item da fila e o devolve; o tipo e a prioridade */
/* do item sao devolvidos nos parametros "tipo" e "prio". */
/* retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro */
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
	if (f == NULL || f->prim == NULL || !tipo || !prio)
		return NULL;
	struct fpnodo_t *aux = f->prim;
	f->prim = aux->prox;
	if (tipo)
		*tipo = aux->tipo;
	if (prio)
		*prio = aux->prio;
	void *item = aux->item;
	free(aux);
	f->num--;
	return item;
}

/* informa o numero de itens na fila. */
/* Retorno: N >= 0 ou -1 se erro. */
int fprio_tamanho (struct fprio_t *f){
	if (f == NULL)
		return -1;
	return f->num;
}

/* imprime o conteudo da fila no formato "(tipo prio) (tipo prio) ..." */
/* para cada item deve ser impresso seu tipo e sua prioridade, com um */
/* espaço entre valores, sem espaços antes ou depois e sem nova linha. */
void fprio_imprime (struct fprio_t *f){
  if (f == NULL)
		  return;
	struct fpnodo_t *aux = f->prim;
	while (aux->prox != NULL){
	    printf("(%d %d) ", aux->tipo, aux->prio);
		  aux = aux->prox;
	}
  printf("(%d %d)", aux->tipo, aux->prio);
}
