#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"
#include "theboys.h"
#include "fprio.h"
#include "fila.h"
#include <math.h>

/* representa um evento com todas as informacoes possiveis, as quais */
/* podem ser utilizadas ou nao. */
/* causara mudancas de estado na simulacao discreta. */
struct evento_t{
    int tempo;
    int tipo;
    int info1;
    int info2; 
};

struct coord_t{
    int x;
    int y;
}

struct coord_t cria_coord(int x, int y){
    struct coord c;
    c.x = int x;
    c.y = int y;
}

// (max - min + 1) gera um número entre 0 e (max - min)
// Somando min, temos o deslocamento do resultado para o intervalo [min, max]
long aleat(long min, long max)
{
  return rand() % (max - min + 1) + min;
}

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

int dist_coord(struct coord_t c1, struct coord_t c2){
    return sqrt(pow(c2.x - c1.x) + pow(c2.y - c1.y));     
}

/* une as habilidades de todos os herois presentes em uma base */
struct cjto_t *hab_uniao(struct mundo_t *w, int id_b){
    struct cjto_t *cjto_hab = cjto_cria(

}

/* representa um heroi H chegando em uma base B no instante T, para depois esperar para entrar na fila ou desistir */
void chega(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    if (h->morto)
        return;
    h->id_b = b->id_b; /* atualiza a base do heroi */
    int tempo = ev->tempo;
    int espera, tipo_ev;
    char *texto;
    if (cjto_card(b->presentes) < (b->limite) && fila_tamanho(b->espera) == 0)
        espera = 1; /* simboliza o valor logico verdadeiro, e nao a cardinalidade da fila de espera */
    else espera = (h->paciencia) > (10*fila_tamanho(b->espera));
    if (espera){
        tipo_ev = ESPERA;
        texto = "ESPERA";
    }
    else {
        tipo_ev = DESISTE;
        texto = "DESISTE";
    }
    struct evento_t *evento = cria_evento(tempo, tipo_ev, h->id_h, b->id_b);
    if (!evento)
        return;
    int teste = fprio_insere(w->lef, evento, tipo_ev, evento->tempo);
    if (teste < 0)
        return;   
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) %s\n", tempo, h->id_h, b->id_b, cjto_card(b->presentes), b->limite, texto);    
}

/* representa a entrada do heroi na fila de espera */
void espera(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (h->morto)
        return;
    if (!(fila_insere(b->espera, h->id_h)))
        return;
    struct evento_t *evento = cria_evento(tempo, AVISA, h->id_h, b->id_b); /* h->id_h nao eh usado mas precisa ser passado, pois eh um cria_evento para todos os eventos */
    if (!evento)
        return;
    int teste = fprio_insere(w->lef, evento, AVISA, tempo);
    if (teste < 0)
        return;
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, h->id_h, b->id_b, fila_tamanho(b->espera));
    }    
}

/* representa a desistencia de um heroi em esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (h->morto)
        return;
    int base_destino = aleat(0, w->qtd_b - 1);
    struct evento_t *evento = cria_evento(tempo, VIAJA, h->id_h, base_destino);
    if (!evento)
        return;     
    int teste = fprio_insere(w->lef, evento, VIAJA, tempo);
    if (teste < 0)
        return;
    printf("%6d: DESIST HEROI %2d BASE %d", tempo, h->id_h, b->id_b);
}

/* representa que o porteiro da dada base eh avisado de que liberou uma vaga. */
/* verifica a fila de espera. */
void avisa(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, b->id_b, cjto_card(b->presentes), b->limite);
    printf(" ]\n");
    while (cjto_card(b->presentes) < b->limite && fila_tamanho(b->espera) > 0){
        int heroi;
        fila_retira(b->espera, &heroi);
        int teste = cjto_insere(b->presentes, w->vet_h[heroi]);
        if (teste < 0)
            return;
        struct evento_t *evento = cria_evento(tempo, ENTRA, heroi, b->id_b);
        if (!evento)
            return;
        teste = fprio_insere(w->lef, evento, ENTRA, evento->tempo);
        if (teste < 0)
            return;
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d", tempo, b->id_b, h->id_h);
    }

}

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (h->morto)
        return;
    int tpb = 15 + (h->paciencia)*aleat(1, 20);
    struct evento_t *evento = cria_evento(tempo + tpb, SAI, h->id_h, b->id_b);
    if (!evento)
        return;
    int teste = fprio_insere(w->lef, evento, SAI, evento->tempo);
    if (teste < 0)
        return;    
    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, h->id_h, b->id_b, cjto_card(b->presentes), b->limite, tempo + tpb);
}

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct heroi_t *b = w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (h->morto)
        return;
    cjto_retira(b->presentes, h->id_h);
    int base_destino = aleat(0, w->qtd_b - 1);
    struct evento_t *viagem = cria_evento(tempo, VIAJA, h->id_h, base_destino);
    struct evento_t *aviso = cria_evento(tempo, AVISA, h->id_h, b->id_b);
    if (!viagem || !aviso)
        return;
    int teste1 = fprio_insere(w->lef, viagem, VIAJA, tempo);
    int teste2 = fprio_insere(w->lef, aviso, AVISA, tempo);
    if (teste1 < 0 || teste2 < 0)
        return;
    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, h->id_h, b->id_b, cjto_card(b->presentes), b->limite);
}

/* representa a viagem do heroi para uma base, agendando e avisando o ponteiro */
void viaja(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[h->id_b];
    struct base_t *d = w->vet_b[ev->info2];
    if (h->morto)
        return;
    distancia = dist_coord(b->local, d->local);
    int duracao = distancia/(h->speed);
    struct evento_t *evento = cria_evento(tempo + duracao, CHEGA, h->id_h, d->id_b);
    if (!evento)
        return;
    int teste = fprio_retira(w->lef, evento, CHEGA, evento->tempo);
    if (teste < 0)
        return;
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d", tempo, h->id_h, b->id_b, d->id_b, distancia, h->speed, tempo + duracao); 
}

/* representa a morte de um heroi, liberando uma nova vaga e avisando o porteiro */
void morre(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct heroi_t *h = w->vet_h[ev->info1];
    struct base_t *b = w->vet_b[h->id_b];
    struct missao_t *m = w->vet_m[ev->info2].
    int tempo = ev->tempo;
    if (!b->presentes)
        return;
    printf("%6d: MORRE HEROI %2d MISSAO %d", tempo, h->id_h, m->id_m);
    if (cjto_retira(b->presentes, h->id_h) < 0)
        return;
    h->morreu = true;
    struct evento_t *evento = cria_evento(tempo, AVISA, h->id_h, ???)
    if (!evento)
        return;
    int teste = fprio_insere(lef, evento, AVISA, evento->tempo);
    if (teste < 0)
        return;    
}

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *w, struct evento_t *ev, struct fprio_t *lef){
    struct missao_t *m = w->vet_m[ev->info1];
    int tempo = ev->tempo;    
    dist_coord(
    
}

/* representa o fim da simulacao */
void fim(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h;
    struct base_t *b;
    int tempo = ev->tempo;
    
    printf("%6d: FIM", T_FIM_DO_MUNDO);
    printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [ %d %d ... ]")
}

/* cria os primeiros eventos e agenda o fim do mundo */
void inicio(struct mundo_t *w);
