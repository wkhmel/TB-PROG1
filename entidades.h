#ifndefd ENTIDADES
#define ENTIDADES

#include "fprio.h"
#include "conjunto.h"

struct heroi_t{
    int id_heroi; /* id do heroi */
    struct cjto_t *skills; /* struct contendo o conjunto de habilidades do heroi */
    int paciencia; /* valor inteiro que representa a paciencia do heroi */
    int speed; /* valor inteiro que representa a velocidade do heroi */
    int exp; /* valor inteiro que representa a experiencia do heroi */
    int id_base; /* id da base em que o heroi se encontra atualmente */
};

struct base_t{
    int id_base; /* numero de identificacao dessa base */ 
    int limite; /* capacidade maxima suportada por essa base */
    struct cjto_t *presentes; /* quantos herois essa base tem */
    struct lista_t *espera; /* fila de herois na lista de espera */
    struct coord_t *local; /* coordenadas X e Y da base */ 
};

struct missao_t{
    int id_missao; /* id dessa missao */
    struct cjto_t *skills /* habilidades requeridas para participar dessa missao */
    struct coord_t *local; /* coordenadas X e Y da missao */
};

struct world{
    int num_h; /* qtd total de herois no mundo */
    int *vet_h; /* vetor de herois */
    int num_b; /* qtd total de bases no mundo */
    int *vet_b; /* vetor de bases */
    int num_m; /* qtd total de missoes no mundo */
    int *vet_m; /* vetor de missoes */
    int num_s /* qtd total de habilidades (skills) no mundo */
    int *vet_s /* vetor de habilidades */
    
}

