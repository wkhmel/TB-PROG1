#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"
#include "theboys.h"
#include "fprio.h"
#include "fila.h"

/* representa um evento com todas as informacoes possiveis, as quais */
/* podem ser utilizadas ou nao. */
/* causara mudancas de estado na simulacao discreta. */
struct evento_t{
    int tempo;
    int tipo;
    int info1;
    int info2;
};

/* cria um novo evento, retornando um ponteiro para ele ou NULL em caso de erro */
struct *cria_evento(int tempo, int tipo, int info1, int info2){
    struct evento_t *ev = malloc(sizeof(struct evento_t));
    if (!ev)
        return NULL;
    ev->tempo = tempo;
    ev->tipo = tipo;
    ev->info1 = info1;
    ev->info2 = info2;
    return evento;
}

void atualiza_tempo(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    w->tempo = ev->tempo;
}

/* representa um heroi H chegando em uma base B no instante T, para depois esperar para entrar na fila ou desistir */
void chega(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    h->id_bh = b->id_b; /* atualiza a base do heroi */
    int tempo = ev->tempo;
    int espera;
    if (cjto_card(b->presentes) < (b->limite) && fila_tamanho(b->espera) == 0)
        espera = 1; /* valor logico verdadeiro */
    else espera = (h->paciencia) > (10*fila_tamanho(b->espera));
    if (espera == 1)
        EVENTO ESPERA
    else
        EVENTO DESISTE
}

/* representa a entrada do heroi na fila de espera */
void espera(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;

    if (fila_insere(b->espera, h->id_h) == 0)
        return;
    if (    
    
}

/* representa a desistencia de um heroi em esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    int base_destino = aleat(0, w->qtd_b);
    struct evento_t *evento = cria_evento(tempo, AVISA, h->id_h, b->id_b)
}

/* representa que o porteiro da dada base eh avisado e verifica a fila de espera */
void avisa(struct mundo_t *w, struct evento_t *ev){
    
}

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(struct mundo_t *w, struct evento_t *ev);

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(struct mundo_t *w, struct evento_t *ev);

/* representa a viagem do heroi para uma base, agendando e avisando o ponteiro */
void viaja(struct mundo_t *w, struct evento_t *ev);

/* representa a morte de um heroi, liberando uma nova vaga e avisando o porteiro */
void morre(struct mundo_t *w, struct evento_t *ev);

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *w, struct evento_t *ev);

/* representa o fim da simulacao */
void fim(struct mundo_t *w);

/* cria os primeiros eventos e agenda o fim do mundo */
void inicio(struct mundo_t *w);
