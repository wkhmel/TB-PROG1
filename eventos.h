#ifndef EVENTOS
#define EVENTOS

#include "theboys.h"
#include "fprio.h"

/* eventos que causarao as mudancas de estado na simulacao discreta */

/* representa um evento do tipo um, que tem tempo, heroi e base */
struct ev_t_um();

/* representa um evento que tem apenas tempo e base, como o caso do avisa */
struct ev_t_dois();

/* representa um evento que usa apenas tempo e missao */
struct ev_t_tres();

/* cria um novo evento, retornando um ponteiro para ele ou NULL em caso de erro */
struct *cria_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2);

/* representa um heroi H chegando em uma base B no instante T, para depois esperar para entrar na fila ou desistir */
void chega(struct mundo_t *m, struct ev_t_um *ev);

/* representa a entrada do heroi na fila de espera */
void espera(struct mundo_t *m, struct ev_t_um *ev);

/* representa a desistencia de um heroi em esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(struct mundo_t *m, struct ev_t_um *ev);

/* representa que o porteiro da dada base eh avisado e verifica a fila de espera */
void avisa(struct mundo_t *m, struct ev_t_dois *ev);

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(struct mundo_t *m, struct ev_t_um *ev);

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(struct mundo_t *m, struct ev_t_um *ev);

/* representa a viagem do heroi para uma base, agendando e avisando o ponteiro */
void viaja(struct mundo_t *m, struct ev_t_um *ev);

/* representa a morte de um heroi, liberando uma nova vaga e avisando o porteiro */
void morre(struct mundo_t *m, struct ev_t_um *ev);

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *m, struct ev_t_tres *ev);

/* representa o fim da simulacao */
void fim(struct mundo_t *m);

/* cria os primeiros eventos e agenda o fim do mundo */
void inicio(struct mundo_t *m);

#endif
