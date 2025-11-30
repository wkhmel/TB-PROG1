#include <std.lib>
#include <math.h>
#include "ferramentas.h"

struct coord_t{
    int x;
    int y;
};

struct dist_base{
    int id;
    int distancia;
};

struct coord_t cria_coord(int x, int y){
    struct coord c;
    c.x = int x;
    c.y = int y;
};

// (max - min + 1) gera um número entre 0 e (max - min)
// Somando min, temos o deslocamento do resultado para o intervalo [min, max]
long aleat(long min, long max)
{
  return rand() % (max - min + 1) + min;
}

int dist_coord(struct coord_t c1, struct coord_t c2){
    return sqrt(pow(c2.x - c1.x) + pow(c2.y - c1.y));     
}

void ordena_dist(struct dist_base v[], int qtd){
    int menor;
    for (int x = 0; x < qtd - 1; x++){
        menor = x;
        for (y = i + 1; y < qtd; y++){
            if (v[y]->distancia < vet_dist[min]->distancia)
                menor = y;
            if (menor != x){
                /* faz a troca entre o antigo menor e o atual menor */
                struct dist_base aux = v[x];
                v[x] = v[y];
                v[y] = aux;
            }                
        }
    }
}
