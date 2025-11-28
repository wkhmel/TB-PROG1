#ifndef EVENTOS
#define EVENTOS
#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 10

#include "theboys.h"
#include "fprio.h"
#include "entidades.h" 

/* eventos que causarao as mudancas de estado na simulacao discreta */
/* tem varios tipos, so mudando a informacao passada em info1 e info2 */
struct evento_t;

/* coordenadas x e y */
struct coord_t;

/* cria uma nova coordenada */
struct coord_t cria_coord(int x, int y);

/* cria um novo evento, retornando um ponteiro para ele ou NULL em caso de erro */
struct evento_t *cria_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2);

/* atualiza o tempo do mundo para o do evento */
void atualiza_tempo(struct mundo_t *m, struct evento_t *ev);

int dist_coord(struct coord_t c1, struct coord_t c2);

/* representa um heroi H chegando em uma base B no instante T, para depois esperar para entrar na fila ou desistir */
void chega(struct mundo_t *m, struct evento_t *ev);

/* representa a entrada do heroi na fila de espera */
void espera(struct mundo_t *m, struct evento_t *ev);

/* representa a desistencia de um heroi em esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(struct mundo_t *m, struct evento_t *ev);

/* representa que o porteiro da dada base eh avisado e verifica a fila de espera */
void avisa(struct mundo_t *m, struct evento_t *ev);

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(struct mundo_t *m, struct evento_t *ev);

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(struct mundo_t *m, struct evento_t *ev);

/* representa a viagem do heroi para uma base, agendando e avisando o ponteiro */
void viaja(struct mundo_t *m, struct evento_t *ev);

/* representa a morte de um heroi, liberando uma nova vaga e avisando o porteiro */
void morre(struct mundo_t *m, struct evento_t *ev);

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *m, struct evento_t *ev);

/* representa o fim da simulacao */
void fim(struct mundo_t *m);

/* cria os primeiros eventos e agenda o fim do mundo */
void inicio(struct mundo_t *m);

#endif
