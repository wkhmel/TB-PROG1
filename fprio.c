#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

/* cria uma fila vazia */
struct fprio_t *fprio_cria (){
        struct fprio_t *novafila = malloc(sizeof(struct fprio_t));
        if (!(novafila))
                return NULL;
        novafila->num = 0;
        novafila->prim = NULL;
        novafila->fim = NULL;
        return novafila;
};

/* destroi todos os nodos da fila de prioridade e a libera */
struct fprio_t *fprio_destroi (struct fprio_t *f){
        if (f != NULL){
                struct fpnodo_t *aux_atual = f->prim;
                struct fpnodo_t *aux_prox;
                while (aux_atual != NULL){
                        aux_prox = aux_atual->prox;
                        free(aux_atual->item);
                        free(aux_atual);
                        aux_atual = aux_prox;
                }
                free(f);
        }
        return NULL;
}

/* insere um elemento na fila de acordo com a sua prioridade e */
/* verifica se o item ja nao esta na fila. retorna o numero de */
/* itens ou retorna -1 se der erro. */
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
        struct fpnodo_t *nodo = malloc(sizeof(struct fpnodo_t));
        if (!(f) || !(nodo))
                return -1;
        /* verifica se nao ha ponteiros repetidos */
        struct fpnodo_t *temp = f->prim;
        while (temp != NULL){
                if (temp->item == item)
                        return -1;
                temp = temp->prox;
        }
        nodo->prio = prio;
        nodo->tipo = tipo;
        nodo->item = item;
        nodo->prox = NULL;
        struct fpnodo_t *aux_ant = NULL;
        struct fpnodo_t *aux = f->prim;

        while (aux != NULL && prio >= aux->prio){
                aux_ant = aux;
                aux = aux->prox;
        }
        if (!aux_ant){
                nodo->prox = f->prim;
                f->prim = nodo;
        }
        else{
                nodo->prox = aux;
                aux_ant->prox = nodo;
        }
        if (!nodo->prox)
                f->fim = nodo;
        f->num++;
        return f->num;
}

/* retira o primeiro elemento da fila e o devolve. */
/* o tipo e a prioridade sao devolvidos nos parametros dos ponteiros. */
/* retorna NULL se erro ou um ponteiro para o item removido. */
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
        if (!(f) || f->num == 0)
                return NULL;
        struct fpnodo_t *aux = f->prim;
        *tipo = aux->tipo;
        *prio = aux->prio;
        void *item = aux->item;
        f->prim = aux->prox;
        free(aux);
        f->num--;
        if (!f->prim)
                f->fim = NULL;
        return item;
}

/* informa o numero de itens na fila. */
/* retorna n >= 0 ou -1 se erro. */
int fprio_tamanho (struct fprio_t *f){
        if (!(f))
                return -1;
        return f->num;
}

/* imprime o conteudo da fila no formato "(tipo prio) (tipo prio) ..."" */
void fprio_imprime (struct fprio_t *f){
        if (f == NULL || f->num == 0)
                return;
        struct fpnodo_t *aux = f->prim;
        while (aux->prox != NULL){
                printf("(%d %d) ", aux->tipo, aux->prio);
                aux = aux->prox;
        }
        printf("(%d %d)", aux->tipo, aux->prio);
}

