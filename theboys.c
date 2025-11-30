// programa principal do projeto "The Boys - 2024/2"
// Autor: Melissa Goulart Kemp, GRR 20255413
#include <stdlib.h>
#include "entidades.h"
#include "simulacao.h"
#include "ferramentas.h"
#include "eventos.h"
#include "fprio.h"

// programa principal
int main ()
{
  // iniciar o mundo
  struct mundo_t *w;
  struct evento_t *ev;
  srand(0);
  // executar o laço de simulação
  w = cria_mundo();
  while (verifica_tempo(w)){
    inicia_eventos(w);
    atualiza_tempo(w, ev);
    simula_eventos(w);
    destroi_evento(ev);
  }
  // destruir o mundo
  destroi_mundo(w);
  return 0;
}

