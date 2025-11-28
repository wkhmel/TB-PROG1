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
void chega(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    h->id_b = b->id_b; /* atualiza a base do heroi */
    int tempo = ev->tempo;
    int espera, tipo_ev;
    if (cjto_card(b->presentes) < (b->limite) && fila_tamanho(b->espera) == 0)
        espera = 1; /* simboliza o valor logico verdadeiro, e nao a cardinalidade da fila de espera */
    else espera = (h->paciencia) > (10*fila_tamanho(b->espera));
    if (espera == 1)
        tipo_ev = ESPERA;
    else tipo_ev = DESISTE;
    struct evento_t *evento = cria_evento(tempo, tipo_ev, h->id_h, b->id_b);
    if (evento)
        fprio_insere(lef, evento, tipo_ev, evento->tempo);
}

/* representa a entrada do heroi na fila de espera */
void espera(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (fila_insere(b->espera, h->id_h)){
        struct evento_t *evento = cria_evento(tempo, AVISA, h->id_h, b->id_b);
        if (evento)
                fprio_insere(lef, evento, AVISA, tempo);
    }    
}

/* representa a desistencia de um heroi em esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    int base_destino = aleat(0, w->qtd_b - 1);
    struct evento_t *evento = cria_evento(tempo, AVISA, h->id_h, base_destino);
    if (evento)     
        int teste = fprio_insere(lef, evento, AVISA, tempo);
    if (teste < 0)
        return;

}

/* representa que o porteiro da dada base eh avisado e verifica a fila de espera */
void avisa(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    while (cjto_card(b->presentes) < b->limite && fila_tamanho(b->espera) > 0){
        int heroi;
        fila_retira(b->espera, &heroi);
        int teste = cjto_insere(b->presentes, w->vet_h[heroi]);
        if (teste < 0)
            return;
        struct evento_t *evento = cria_evento(tempo, ENTRA, heroi, b->id_b);
        if (evento)
            teste = fprio_insere(lef, evento, ENTRA, evento->tempo);
        if (teste < 0)
            return;
    }
}

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    int tpb = 15 + (h->paciencia)*aleat(1, 20);
    struct evento_t *evento = cria_evento(tempo + tpb, SAI, h->id_h, b->id_b);
    if (evento)
        int teste = fprio_insere(lef, evento, SAI, evento->tempo);
    if (teste < 0)
        return;    
/* imprimir aqui caso a insercao na lef de certo */
}

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct heroi_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    cjto_retira(b->presentes, h->id_h);
    int base_destino = aleat(0, w->qtd_b - 1);
    struct evento_t *viagem = cria_evento(tempo, VIAJA, h->id_h, base_destino);
    if (viagem)
        int teste = fprio_insere(lef, viagem, VIAJA, tempo);
    if (teste < 0)
        return;
    struct evento_t *aviso = cria_evento(tempo, AVISA, b->id_b);
    if (aviso)
        teste = fprio_insere(lef, aviso, AVISA, tempo); 
    if (teste < 0)
        return;

}

/* representa a viagem do heroi para uma base, agendando e avisando o ponteiro */
void viaja(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *d = w->vet_b[ev->info2];
    int duracao = (dist_coord(h->id_b, d->id_b))/(h->speed);
    struct evento_t *evento = cria_evento(tempo + duracao, CHEGA, h->id_h, d->id_b);
    if (evento)
        int teste = fprio_retira(lef, evento, CHEGA, evento->tempo);
    if (teste < 0)
        return;

}

/* representa a morte de um heroi, liberando uma nova vaga e avisando o porteiro */
void morre(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (cjto_retira(b->presentes, h->id_h) > 0)
        h->morreu = true;
    struct evento_t *evento = cria_evento(tempo, AVISA, h->id_h, ???)
    if (evento)
        int teste = fprio_insere(lef, evento, AVISA, evento->tempo);
    if (teste < 0)
        return;

}

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct missao_t *m = w->vet_m[ev->info1];
    int tempo = ev->tempo;
    

}

/* representa o fim da simulacao */
void fim(struct mundo_t *w);

/* cria os primeiros eventos e agenda o fim do mundo */
void inicio(struct mundo_t *w);
