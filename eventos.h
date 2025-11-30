#ifndef EVENTOS_H
#define EVENTOS_H
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
#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "eventos.h"
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"
#include "ferramentas.h"

/* representa um evento com todas as informacoes possiveis, as quais */
/* podem ser utilizadas ou nao. */
/* causara mudancas de estado na simulacao discreta. */
struct evento_t{
    int tempo;
    int tipo;
    int info1;
    int info2; 
};

/* adiciona um novo evento, retornando 1 em sucesso e 0 em falha */
int adiciona_evento(struct mundo_t *w, int tempo, int tipo, int info1, int info2);

/* verifica se os ponteiros do mundo nao sao nulos */
int verifica_mundo(struct mundo_t *w);

/* inicia a simulacao dos eventos, retornando 1 em sucesso e 0 em falha */
/* marca a chegada dos herois e agenda as missoes e o fim do mundo */
int inicia_eventos(struct mundo_t *m);

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

/* une todas as habilidades dos herois de uma mesma base */
/* verifica se o heroi esta naquela base e, se sim, adiciona suas habilidades ao conjunto */
struct cjto_t *skills_b(struct mundo_t *w, int id_b);

/* retorna o id do heroi de maior xp de uma base cujo id eh passado como parametro */
int maior_xp(struct mundo_t *w, int id_b);

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *m, struct evento_t *ev);

/* retorna o tempo atual do mundo */
int tempo_mundo(struct mundo_t *w)

/* diz se o heroi morreu ou nao, mantendo a struct opaca na simulacao */
int morte_heroi(struct mundo_t *w, struct evento_t *ev);

/* representa o fim da simulacao */
void fim(struct mundo_t *m, struct evento_t *ev);

void simula_eventos(struct mundo_t *w);

#endif
