#ifndef ENTIDADES
#define ENTIDADES
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS 5*N_HABILIDADES
#define N_BASES N_HEROIS/5
#define N_MISSOES T_FIM_DO_MUNDO/100
#define N_COMPOSTOS_V N_HABILIDADES*3

struct heroi_t();

struct base_t();

struct missao_t();

struct mundo_t();

/* aqui, vou colocar as structs que criam e destroem cada uma das entidades */
struct heroi_t *cria_heroi(int id_h);

struct heroi_t *destroi_heroi(struct mundo_t *h);

struct base_t *cria_base(int id_b);

struct base_t *destroi_base(struct base_t *b);

struct missao_t *cria_missao(int id_m);

struct missao_t *destroi_missao(struct missao_t *m);

struct missao_t *cria_mundo();

struct missao_t *destroi_mundo(struct mundo_t *w);

#endif
