// programa principal do projeto "The Boys - 2024/2"
// Autor: Melissa Goulart Kemp, GRR 20255413
#include <stdlib.h>
#include "entidades.h"
#include "eventos.h"
#include "fprio.h"

// programa principal
int main (){
  // iniciar o mundo
  struct mundo_t *w;
  srand(0); 

  w = cria_mundo();

  // agenda os eventos iniciais uma unica vez
  inicia_eventos(w);

  // roda a simulacao do mundo
  simula_eventos(w);

  // destroi tudo no fim da simulacao
  destroi_mundo(w);

  return 0;
}
