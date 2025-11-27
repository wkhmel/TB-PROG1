#include "fprio.h"
#include "conjunto.h"
#include "fila.h"

struct heroi_t{
    int id_h; /* id do heroi */
    struct cjto_t *skills; /* struct contendo o conjunto de habilidades do heroi */
    int paciencia; /* valor inteiro que representa a paciencia do heroi */
    int speed; /* valor inteiro que representa a velocidade do heroi */
    int exp; /* valor inteiro que representa a experiencia do heroi */
    int id_bh; /* id da base em que o heroi se encontra atualmente */
};

struct base_t{
    int id_b; /* numero de identificacao dessa base */ 
    int limite; /* capacidade maxima suportada por essa base */
    struct cjto_t *presentes; /* conjunto de herois que essa base tem */
    struct lista_t *espera; /* fila de herois na lista de espera */
    struct coord_t local; /* coordenadas X e Y da base */ 
};

struct missao_t{
    int id_m; /* id dessa missao */
    struct cjto_t *skills /* habilidades requeridas para participar dessa missao */
    struct coord_t local; /* coordenadas X e Y da missao */
};

struct world{
    int qtd_h; /* qtd total de herois no mundo */
    struct heroi_t *vet_h; /* vetor de herois */
    int qtd_b; /* qtd total de bases no mundo */
    struct base_t *vet_b; /* vetor de bases */
    int qtd_m; /* qtd total de missoes no mundo */
    struct missao_t *vet_m; /* vetor de missoes */
    int qtd_s /* qtd total de habilidades no mundo */
    int qtd_v /* qtd de compostos V disponiveis */
    struct coord_t tam_m /* tamanho maximo do mundo. nao precisa ser alocado porque eh constante. 1 unidade = 1 metro real */
    int tempo /* tempo atual desse mundo. 1 unidade = 1 minuto real */
}

/* aqui, vou colocar as structs que criam e destroem cada uma das entidades */
struct heroi_t *cria_heroi(int id_h);

struct heroi_t *destroi_heroi(struct mundo_t *h);

struct base_t *cria_base(int id_b);

struct base_t *destroi_base(struct base_t *b);

struct missao_t *cria_missao(int id_m);

struct missao_t *destroi_missao(struct missao_t *m);

#endif
