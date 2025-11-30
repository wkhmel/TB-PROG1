#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H
#include <math.h>
#include <stdlib.h>

struct coord_t{
    int x;
    int y;
};

struct dist_base{
    int id;
    int distancia;
};

long aleat(long min, long max);

int dist_coord(struct coord_t c1, struct coord_t c2);

void ordena_dist(int vet_dist[], int vet_id[], int qtd);

#endif
