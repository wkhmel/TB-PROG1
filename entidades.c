#include <stdio.h>
#include <stdlib.h>
#include "ferramentas.h"
#include "entidades.h"
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"

/* cria um heroi. retorna o ponteiro para o heroi ou NULL em caso de erro. */
struct heroi_t *cria_heroi(int id){
    struct heroi_t *h;
    h = malloc(sizeof(struct heroi_t));
    if (!h)
        return NULL;
    h->id_h = id;
    h->skills = cjto_aleat(aleat(1, 3), N_HABILIDADES);
    h->paciencia = aleat(0, 100);
    h->speed = aleat(50, 5000);
    h->exp = 0;
    h->id_b = -1;
    h->morto = false;

    return h;
}

/* funcao que destroi o heroi e todas as suas estruturas e devolve o id do heroi em um ponteiro. */
/* retorna NULL. */
struct heroi_t *destroi_heroi(struct heroi_t *h){
    if (!h)
        return NULL;
    if (h->skills)
        cjto_destroi(h->skills);
    free(h);
    return NULL;
}

struct base_t *cria_base(int id){
    struct base_t *b;
    b = malloc(sizeof(struct base_t));
    if (!b)
        return NULL;
    b->id_b = id;
    b->limite = aleat(3, 10);
    b->presentes = cjto_cria((b->limite)); /* cria conjunto vazio */
    b->espera = fila_cria(); /* cria fila de espera vazia */
    b->missoes = 0;
    b->max_fila = 0;

    return b;
}

struct base_t *destroi_base(struct base_t *b){
    if (!b)
        return NULL;
    if (b->presentes)
        cjto_destroi(b->presentes);
    if (b->espera)
        fila_destroi(b->espera);
    free(b);
    return NULL;
}

struct missao_t *cria_missao(int id){
    struct missao_t *m;
    m = malloc(sizeof(struct missao_t));
    if (!m)
        return NULL;
    m->id_m = id;
    m->skills = cjto_aleat(aleat(6,10), N_HABILIDADES);
    m->tentativas = 0;
    m->realizou = false;
    m->local.x = aleat(0, N_TAMANHO_MUNDO - 1);
    m->local.x = aleat(0, N_TAMANHO_MUNDO - 1);
    return m;
}

struct missao_t *destroi_missao(struct missao_t *m){
    if (!m)
        return NULL;
    if (m->skills)
        cjto_destroi(m->skills);
    free(m);
    return NULL;
}

/* inicializacao */
struct mundo_t *cria_mundo(){
    struct mundo_t *w;
    w = malloc(sizeof(struct mundo_t));
    if (!w)
        return NULL;
    w->qtd_h = N_HEROIS;

    for (int i = 0; i < w->qtd_h; i++){
        w->vet_h[i] = cria_heroi(i);
        if (!w->vet_h[i]){
            destroi_mundo(w);
            return NULL;
        }
    }
    w->qtd_b = N_BASES;

    for (int i = 0; i < w->qtd_b; i++){
        w->vet_b[i] = cria_base(i);
        if (!w->vet_b[i]){
            destroi_mundo(w);
            return NULL;
        }
    }
    w->qtd_m = N_MISSOES;

    for (int i = 0; i < w->qtd_m; i++){
        w->vet_m[i] = cria_missao(i);
        if (!w->vet_m[i]){
            destroi_mundo(w);
            return NULL;
        }
    }

    w->qtd_hab = N_HABILIDADES;
    w->qtd_v = N_COMPOSTOS_V;
    (w->tam_m).x = N_TAMANHO_MUNDO;
    (w->tam_m).y = N_TAMANHO_MUNDO;
    w->tempo = T_INICIO;
    w->lef = fprio_cria();
    w->total_eventos = 0;
    w->missoes_cumpridas = 0;
    w->mortes = 0;
    return w;
}

struct mundo_t *destroi_mundo(struct mundo_t *w){
    if (!w)
        return NULL;
    for (int i = 0; i < w->qtd_h; i++){
        destroi_heroi(w->vet_h[i]);
    }

    for (int i = 0; i < w->qtd_b; i++){
        destroi_base(w->vet_b[i]);
    }

    for (int i = 0; i < w->qtd_m; i++){
        destroi_missao(w->vet_m[i]);
    }

    fprio_destroi(w->lef);

    free(w);
    return NULL;
}
