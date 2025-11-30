#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H
#include <math.h>
#include <stdlib.h>

/* estrutura de coordenadas x e y */
struct coord_t{
    int x;
    int y;
};

/* estrutura que armazena o id de uma base e a distancia dela ate algum lugar. */
/* eh util para ver qual eh a base de menor distancia ate uma missao. */
struct dist_base{
    int id;
    int distancia;
};

/* funcao de aleatorizacao */
long aleat(long min, long max);

/* calcula a distancia entre coordenadas */
int dist_coord(struct coord_t c1, struct coord_t c2);

/* ordena as distancias de uma estrutura contendo id e distancia e */
/* recebe um parametro com a quantidade de elementos */
void ordena_dist(struct dist_base v[], int qtd);

#endif
