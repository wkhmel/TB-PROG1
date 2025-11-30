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
  // executar o laço de simulação
  w = cria_mundo();
  while (tempo_mundo(w)){
    inicia_eventos(w);
    simula_eventos(w);
  }
  // destruir o mundo
  destroi_mundo(w);
  return 0;
}

