#ifndef ENTIDADES_H
#define ENTIDADES_H
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"
#include "ferramentas.h"
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS 5*N_HABILIDADES
#define N_BASES N_HEROIS/5
#define N_MISSOES T_FIM_DO_MUNDO/100
#define N_COMPOSTOS_V N_HABILIDADES*3

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
    struct cjto_t *skills; /* habilidades requeridas para participar dessa missao */
    struct coord_t local; /* coordenadas X e Y da missao */
    int tentativas; /* qtd de tentativas feitas para essa missao, cumprida ou nao */
    bool realizou;
};

struct mundo_t{
    int qtd_h; /* qtd total de herois no mundo */
    struct heroi_t **vet_h[N_HEROIS]; /* vetor de herois */
    int qtd_b; /* qtd total de bases no mundo */
    struct base_t **vet_b[N_BASES]; /* vetor de bases */
    int qtd_m; /* qtd total de missoes no mundo */
    struct missao_t **vet_m[N_MISSOES]; /* vetor de missoes */
    int qtd_hab; /* qtd total de habilidades no mundo */
    int qtd_v; /* qtd de compostos V disponiveis */
    struct coord_t tam_m; /* tamanho maximo do mundo. nao precisa ser alocado porque eh constante. 1 unidade = 1 metro real */
    int tempo; /* tempo atual desse mundo. 1 unidade = 1 minuto real */
    struct fprio_t *lef;
    int total_eventos; /* qtd de eventos de que participou */
    int missoes_cumpridas; /* qtd de missoes que foram cumpridas */
    int mortes; /* qtd total de mortes no mundo */
};

/* aqui, vou colocar as structs que criam e destroem cada uma das entidades */
struct heroi_t *cria_heroi(int id_h);

struct heroi_t *destroi_heroi(struct heroi_t *h);

struct base_t *cria_base(int id_b);

struct base_t *destroi_base(struct base_t *b);

struct missao_t *cria_missao(int id_m);

struct missao_t *destroi_missao(struct missao_t *m);

struct mundo_t *cria_mundo();

struct mundo_t *destroi_mundo(struct mundo_t *w);

#endif
