#ifndef THEBOYS
#define THEBOYS

/* entidades da simulacao */
struct heroi;
struct base;
struct missao;
struct mundo;

/* eventos que causarao as mudancas de estado na simulacao discreta */

/* representa um heroi H chegando em uma base B no instante T, para depois esperar para entrar na fila ou desistir */
void chega(int tempo, struct heroi, struct base);

/* nesse evento, o heroi entra na determinada fila de espera */
void espera(int tempo, struct heroi, struct base);

/* eh usado quando um heroi desiste de esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(int tempo, struct heroi, struct base);

/* o porteiro da dada base eh avisado e verifica a fila de espera */
void avisa(int tempo, struct base);

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(int tempo, struct heroi, struct base);

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(int tempo, struct heroi, struct base);

/* evento em que o heroi viaja para uma base D, que tambem pode ser a ma */


