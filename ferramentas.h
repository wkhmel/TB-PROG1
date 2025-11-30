#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H
#include <math.h>
#include <stdio.h>
#include "entidades.h"
#include "eventos.h"

struct coord_t;

struct dist_base;

struct coord_t cria_coord(int x, int y);

long aleat(long min, long max);

void atualiza_tempo(struct mundo_t *w, struct evento_t *ev);

int dist_coord(struct coord_t c1, struct coord_t c2);

void ordena_dist(int vet_dist[], int vet_id[], int qtd);

#endif
