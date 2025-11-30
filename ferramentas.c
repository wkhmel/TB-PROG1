#include <stdlib.h>
#include <math.h>
#include "ferramentas.h"

// (max - min + 1) gera um número entre 0 e (max - min)
// Somando min, temos o deslocamento do resultado para o intervalo [min, max]
long aleat(long min, long max){
  return rand() % (max - min + 1) + min;
}

int dist_coord(struct coord_t c1, struct coord_t c2){
    return sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));     
}

void ordena_dist(struct dist_base v[], int qtd){
    int menor;
    for (int x = 0; x < qtd - 1; x++){
        menor = x;
        for (int y = x + 1; y < qtd; y++){
            if (v[y].distancia < v[menor].distancia)
                menor = y;
        }
            if (menor != x){
                /* faz a troca entre o antigo menor e o atual menor */
                struct dist_base aux = v[x];
                v[x] = v[menor];
                v[menor] = aux;
            }                
        }
}
