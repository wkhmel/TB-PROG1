#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

/* funcao que destroi o heroi e todas as suas estruturas e retorna NULL. */
struct heroi_t *destroi_heroi(struct heroi_t *h){
    if (!h)
        return NULL;
    if (h->skills)
        cjto_destroi(h->skills); /* destroi o cjto de habilidades que foi alocado dinamicamente */
    return NULL;
}

/* cria uma base */
struct base_t *cria_base(int id){
    struct base_t *b;
    b = malloc(sizeof(struct base_t));
    if (!b)
        return NULL;
    b->id_b = id;
    b->limite = aleat(3, 10);
    b->presentes = cjto_cria(N_HEROIS); /* cria conjunto vazio com capacidade para ate N_HEROIS */
    b->espera = fila_cria(); /* cria fila de espera vazia */
    b->missoes = 0;
    b->max_fila = 0;

    return b;
}

/* destroi todas as estruturas da base */
struct base_t *destroi_base(struct base_t *b){
    if (!b)
        return NULL;
    if (b->presentes)
        cjto_destroi(b->presentes);
    if (b->espera)
        fila_destroi(b->espera);
    return NULL;
}

/* cria uma missao */
struct missao_t *cria_missao(int id){
    struct missao_t *m;
    m = malloc(sizeof(struct missao_t));
    if (!m)
        return NULL;
    m->id_m = id;
    /* cria um cjto aleatorio de habilidades, que pode ter de 6 a 10 e */
    /* eh selecionado entre todas as 10 habilidades do mundo */
    m->skills = cjto_aleat(aleat(6,10), N_HABILIDADES); 
    m->tentativas = 0;
    m->realizou = false;
    m->local.x = aleat(0, N_TAMANHO_MUNDO - 1);
    m->local.y = aleat(0, N_TAMANHO_MUNDO - 1);
    return m;
}

/* destroi a missao e o conjunto de habilidades dinamicamente alocado */
struct missao_t *destroi_missao(struct missao_t *m){
    if (!m)
        return NULL;
    if (m->skills)
        cjto_destroi(m->skills);
    return NULL;
}

/* inicializacao do mundo */
struct mundo_t *cria_mundo(){
    struct mundo_t *w;
    w = malloc(sizeof(struct mundo_t));
    if (!w)
        return NULL;
    w->qtd_h = N_HEROIS;
    w->qtd_b = N_BASES;
    w->qtd_m = N_MISSOES;

    /* libera os espacos na memoria para todos os vetores */
    /* nas respectivas quantidades */
    w->vet_h = malloc(w->qtd_h*(sizeof(struct heroi_t)));
    w->vet_b = malloc(w->qtd_b*(sizeof(struct base_t)));
    w->vet_m = malloc(w->qtd_m*(sizeof(struct missao_t)));

    /* se houver algum erro em algum desses vetores, destroi o mundo */
    if (!w->vet_h || !w->vet_b || !w->vet_m){
        destroi_mundo(w);
        return NULL;
    }

    /* usa um struct auxiliar para criar um heroi e colocar no vetor daquele indice */
    for (int i = 0; i < w->qtd_h; i++){
        struct heroi_t *aux = cria_heroi(i);
        w->vet_h[i] = *aux;
        free(aux);
    }

    for (int i = 0; i < w->qtd_b; i++){
        struct base_t *aux = cria_base(i);
        w->vet_b[i] = *aux;
        free(aux);
    }

    for (int i = 0; i < w->qtd_m; i++){
        struct missao_t *aux = cria_missao(i);
        w->vet_m[i] = *aux;
        free(aux);
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

/* destroi o mundo e todos os vetores */
struct mundo_t *destroi_mundo(struct mundo_t *w){
    if (!w)
        return NULL;
    for (int i = 0; i < w->qtd_h; i++){
        destroi_heroi(&w->vet_h[i]);
    }
    /* libera o vetor inteiro */
    free(w->vet_h);
    
    for (int i = 0; i < w->qtd_b; i++){
        destroi_base(&w->vet_b[i]);
    }
    free(w->vet_b);
    
    for (int i = 0; i < w->qtd_m; i++){
        destroi_missao(&w->vet_m[i]);
    }
    free(w->vet_m);
    
    fprio_destroi(w->lef);

    free(w);
    return NULL;
}
