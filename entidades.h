#ifndef ENTIDADES
#define ENTIDADES
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"

struct heroi_t();

struct base_t();

struct missao_t();

struct world();

/* aqui, vou colocar as structs que criam e destroem cada uma das entidades */
struct heroi_t *cria_heroi(int id_h);

struct heroi_t *destroi_heroi(struct mundo_t *h);

struct base_t *cria_base(int id_b);

struct base_t *destroi_base(struct base_t *b);

struct missao_t *cria_missao(int id_m);

struct missao_t *destroi_missao(struct missao_t *m);

#endif
