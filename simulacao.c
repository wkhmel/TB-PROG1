#include "simulacao.h"
#include "eventos.h"
#include "fprio.h"
#include "entidades.h"

void simula_eventos(struct mundo_t *w){
    struct evento_t *ev;
    int tipo_evento, tempo, id_h;
    int fim = 0;
    if (!verifica_mundo(w))
        return;
    while (!fim && fprio_tamanho(lef) > 0){
        ev = fprio_retira(w->lef, &tipo_evento, &tempo);
        if (!ev)
            break;
        w->tempo = tempo;
        w->total_eventos++;

    /* escolhe o evento */
        switch (tipo_evento) {
            case CHEGA:
                 chega(w, ev);
                break;
            case ESPERA:
                espera(w, ev);
                break;
            case DESISTE:
                desiste(w, ev);
                break;
            case MORRE:
                morre(w, ev);
                break;
            case ENTRA:
                entra(w, ev);
                break;
            case SAI:   
                sai(w, ev);
                break;
            case VIAJA:
                viaja(w, ev);
                break;
            case AVISA:
                avisa(w, ev);
                break;
            case MISSAO:
                missao(w, ev);
                break;
            case FIM:
                fim(w, ev);
                return;
                fim = 1;
        }

        free(ev);
        ev = NULL;
    }
}

int verifica_tempo(struct mundo_t *w){
    if (w->tempo >= T_FIM_DO_MUNDO)
        return 0;
    return 1;
}
