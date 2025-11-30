#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"

struct heroi_t{
    int id_h; /* id do heroi */
    struct cjto_t *skills; /* struct contendo o conjunto de habilidades do heroi */
    int paciencia; /* valor inteiro que representa a paciencia do heroi */
    int speed; /* valor inteiro que representa a velocidade do heroi */
    int exp; /* valor inteiro que representa a experiencia do heroi */
    int id_b; /* id da base em que o heroi se encontra atualmente */
    bool morto; /* true se morreu, false se permanece vivo */ 
};

struct base_t{
    int id_b; /* numero de identificacao dessa base */ 
    int limite; /* capacidade maxima suportada por essa base */
    struct cjto_t *presentes; /* conjunto de herois que essa base tem */
    struct fila_t *espera; /* fila de herois na lista de espera */
    struct coord_t local; /* coordenadas X e Y da base */ 
    int missoes; /* quantidade de missoes de que essa base participou */
    int max_fila; /* tamanho maximo que a fila de espera atingiu */
};

struct missao_t{
    int id_m; /* id dessa missao */
    struct cjto_t *skills /* habilidades requeridas para participar dessa missao */
    struct coord_t local; /* coordenadas X e Y da missao */
    int tentativas; /* qtd de tentativas feitas para essa missao, cumprida ou nao */
    bool realizou;
};

struct mundo_t{
    int qtd_h; /* qtd total de herois no mundo */
    struct heroi_t *vet_h; /* vetor de herois */
    int qtd_b; /* qtd total de bases no mundo */
    struct base_t *vet_b; /* vetor de bases */
    int qtd_m; /* qtd total de missoes no mundo */
    struct missao_t *vet_m; /* vetor de missoes */
    int qtd_hab; /* qtd total de habilidades no mundo */
    int qtd_v; /* qtd de compostos V disponiveis */
    struct coord_t tam_m; /* tamanho maximo do mundo. nao precisa ser alocado porque eh constante. 1 unidade = 1 metro real */
    int tempo /* tempo atual desse mundo. 1 unidade = 1 minuto real */
    struct fprio_t *lef;
    int total_eventos; /* qtd de eventos de que participou */
    int missoes_cumpridas; /* qtd de missoes que foram cumpridas */
    int mortes; /* qtd total de mortes no mundo */
}

/* cria um heroi. retorna o ponteiro para o heroi ou NULL em caso de erro. */
struct heroi_t *cria_heroi(int id){
    struct heroi_t *h = malloc(sizeof(struct heroi_t));
    if (!h)
        return NULL;
    h->id_h = id;
    h->skills = cjto_cria(aleat(1, 3), N_HABILIDADES);
    h->paciencia = aleat(0, 100);
    h->speed = aleat(50, 5000);
    h->exp = 0;
    h->id_b = -1;
    h->morreu = false;

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
    struct base_t *b = malloc(sizeof(struct base_t));
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
    struct missao_t *m = malloc(sizeof(struct missao_t));
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

struct mundo_t *cria_mundo(){
    struct mundo_t *w = malloc(sizeof(struct mundo_t));
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
