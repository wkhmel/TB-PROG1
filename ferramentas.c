#include <stdlib.h>
#include <math.h>
#include "ferramentas.h"

/* (max - min + 1) gera um valor entre 0 e (max - min) */
long aleat(long min, long max){
  return rand() % (max - min + 1) + min;
}

/* calcula a distancia de dos locais usando a formula da distancia entre coordenadas */
int dist_coord(struct coord_t c1, struct coord_t c2){
    return sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));     
}

/* ordena as distancias usando o algoritmo de selectionsort. */
/* percorre todo o vetor nao ordenado em cada iteracao para */
/* buscar o menor elemento. */
void ordena_dist(struct dist_base v[], int qtd){
    int menor;
    for (int x = 0; x < qtd - 1; x++){
        menor = x;
        for (int y = x + 1; y < qtd; y++){
            if (v[y].distancia < v[menor].distancia) /* se for menor que a menor, temos uma nova menor */
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
