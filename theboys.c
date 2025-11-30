// programa principal do projeto "The Boys - 2024/2"
// Autor: Melissa Goulart Kemp, GRR 20255413
#include <stdlib.h>
#include "entidades.h"
#include "simulacao.h"
#include "ferramentas.h"
#include "eventos.h"

// minimize o uso de variáveis globais

// programa principal
int main ()
{
  // iniciar o mundo
  struct mundo_t *w;
  struct evento_t *ev;
  
  // executar o laço de simulação
  w = cria_mundo();
  inicia_eventos(w);
  while (w->tempo < T_FIM_DO_MUNDO){
    /*Retira o primeiro evento da lista de eventos futuros*/
    ev = retira_lef(retorna_evento(mundo));
    atualiza_relogio(w, ev);
    /*Chama a função que trata o evento*/
    simula_eventos(w);
    /*Liberta a memoria do evento*/
    destroi_evento(ev);
  }
  
  // destruir o mundo
  destroi_mundo(w);
  return 0;
}

