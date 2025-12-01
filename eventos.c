#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "eventos.h"
#include "fprio.h"
#include "conjunto.h"
#include "fila.h"
#include "ferramentas.h"

/* cria um novo evento, retornando um ponteiro para ele ou NULL em caso de erro */
int adiciona_evento(struct mundo_t *w, int tempo, int tipo, int info1, int info2){
    struct evento_t *ev = malloc(sizeof(struct evento_t));
    if (!ev){
        printf("Erro: nao alocou o evento\n");
        return 0;
    }
    ev->tempo = tempo;
    ev->tipo = tipo;
    ev->info1 = info1;
    ev->info2 = info2;
    int teste = fprio_insere(w->lef, ev, tipo, tempo);
    if (teste < 0)
        return 0;
    return 1;
}

/* verifica se os ponteiros do mundo estao funcionando. */
/* em caso de erro, retorna 0; senao, retorna 1. */
int verifica_mundo(struct mundo_t *w){
    if (!w || !w->vet_h || !w->vet_b || !w->vet_m || !w->lef){
        printf("Erro: mundo ou algum de seus atributos eh invalido\n");
        return 0;
    }
    return 1;
}

/* faz os eventos iniciais, agendando as missoes e o fim do mundo */
int inicia_eventos(struct mundo_t *w){
    int base, tempo; 
    if (!verifica_mundo(w))
        return 0;
/* chegada dos herois */
    for (int i = 0; i < w->qtd_h; i++){
        base = aleat(0, w->qtd_b - 1);
        tempo = aleat(0, 4320);
        if (!(adiciona_evento(w, tempo, CHEGA, (w->vet_h[i]).id_h, base)))
            return 0;
    }

/* agendamento das missoes */
    for (int i = 0; i < w->qtd_m; i++){
        tempo = aleat(0, T_FIM_DO_MUNDO);
        if (!(adiciona_evento(w, tempo, MISSAO, (w->vet_m[i]).id_m, -1)))
            return 0;
    }

/* agendamento do fim do mundo */
    if (!adiciona_evento(w, T_FIM_DO_MUNDO, FIM, -1, -1))
        return 0;
    return 1;
}

/* representa um heroi H chegando em uma base B no instante T, para depois esperar para entrar na fila ou desistir */
void chega(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1]; /* eh a struct evento que contem o id do heroi e o da base */
    struct base_t *b = &w->vet_b[ev->info2];
    if (!verifica_mundo(w))
        return;
    h->id_b = b->id_b; /* atualiza a base do heroi */
    int tempo = ev->tempo;
    int espera, tipo_ev;
    char *texto; /* eu criei um char para armazenar a mensagem do tipo de evento para nao ter que printar duas vezes */
    if (cjto_card(b->presentes) < (b->limite) && fila_tamanho(b->espera) == 0)
        espera = 1; /* simboliza o valor logico verdadeiro, e nao a cardinalidade da fila de espera */
    else espera = (h->paciencia) > (10*fila_tamanho(b->espera));
    if (espera){
        tipo_ev = ESPERA;
        texto = "ESPERA";
    }
    else {
        tipo_ev = DESISTE;
        texto = "DESISTE";
    }
    if (!adiciona_evento(w, tempo, tipo_ev, h->id_h, b->id_b))
        return;
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) %s\n", tempo, h->id_h, b->id_b, cjto_card(b->presentes), b->limite, texto);    
}

/* representa a entrada do heroi na fila de espera */
void espera(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1];
    struct base_t *b = &w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (!verifica_mundo(w))
        return;
    if (!(fila_insere(b->espera, h->id_h))){
        printf("Erro: o heroi %d nao foi inserido na fila de espera da base %d\n", ev->info1, ev->info2);
        return;
    } 
    if (!adiciona_evento(w, tempo, AVISA, h->id_h, b->id_b))
        return;
    int atual = fila_tamanho(b->espera);
    if (atual > b->max_fila) /* verifica se a fila atual eh ou nao a maior fila que a base b ja teve */
        b->max_fila = atual;
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, h->id_h, b->id_b, fila_tamanho(b->espera));    
}

/* representa a desistencia de um heroi em esperar para entrar em uma base, e em seguida esse heroi viaja para uma base aleatoria D */
void desiste(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1];
    struct base_t *b = &w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (!verifica_mundo(w))
        return;
    int base_destino = aleat(0, w->qtd_b - 1); /* aleatoriza a base de destino */
    if (!adiciona_evento(w, tempo, VIAJA, h->id_h, base_destino))
        return;
    printf("%6d: DESIST HEROI %2d BASE %d\n", tempo, h->id_h, b->id_b);
}

/* representa que o porteiro da dada base eh avisado de que liberou uma vaga. */
/* verifica a fila de espera. */
void avisa(struct mundo_t *w, struct evento_t *ev){
    struct base_t *b = &w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (!verifica_mundo(w))
        return;
    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, b->id_b, cjto_card(b->presentes), b->limite);
    fila_imprime(b->espera);
    printf(" ]\n");
    /* verifica se a qtd de herois presentes nao excede o limite da base e se ha herois na fila */
    while (cjto_card(b->presentes) < b->limite && fila_tamanho(b->espera) > 0){
        int heroi;
        fila_retira(b->espera, &heroi); /* a variavel heroi recebe o id do heroi removido da fila */
        int teste = cjto_insere(b->presentes, heroi);
        if (teste < 0){
            printf("Erro: o heroi %d nao foi inserido na lista de presentes da base %d\n", heroi, ev->info2);
            return;
        }
        if (!adiciona_evento(w, tempo, ENTRA, heroi, b->id_b))
            return;
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", tempo, b->id_b, heroi);
    }

}

/* representa a entrada do heroi na determinada base, agendando o tempo que vai permanecer la e quando vai sair */
void entra(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1];
    struct base_t *b = &w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (!verifica_mundo(w))
        return;
    int tpb = 15 + (h->paciencia)*aleat(1, 20); /* tempo que o heroi passa na base */
    if (!adiciona_evento(w, tempo + tpb, SAI, h->id_h, b->id_b))
        return;    
    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, h->id_h, b->id_b, cjto_card(b->presentes), b->limite, tempo + tpb);
}

/* representa a saida do heroi da base em que estava, escolhendo uma outra base aonde viajar e avisando o porteiro de que ha uma nova vaga disponivel */
void sai(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1];
    struct base_t *b = &w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (!verifica_mundo(w))
        return;
    cjto_retira(b->presentes, h->id_h); /* retira um presente da base porque o heroi sai dela */
    int base_destino = aleat(0, w->qtd_b - 1); /* sorteia uma base para o heroi ir, podendo ser a mesma ou nao */
    /* o heroi viaja e o porteiro da base em que ele estava eh avisado ao mesmo tempo */
    if (!adiciona_evento(w, tempo, VIAJA, h->id_h, base_destino) || !adiciona_evento(w, tempo, AVISA, -1, base_destino)) 
        return;
    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, h->id_h, b->id_b, cjto_card(b->presentes), b->limite);
}

/* representa a viagem do heroi para uma base, agendando e avisando o ponteiro */
void viaja(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1];
    struct base_t *b = &w->vet_b[h->id_b];
    struct base_t *d = &w->vet_b[ev->info2];
    int tempo = ev->tempo;
    if (!verifica_mundo(w))
        return;
    int distancia = dist_coord(b->local, d->local); /* dist da  base atual ate a base que ira ser visitada pelo heroi */
    int duracao = distancia/(h->speed); /* o tempo que ele vai levar para ir depende de quao longe a base eh e da velocidade do heroi */
    if (!adiciona_evento(w, tempo + duracao, CHEGA, h->id_h, d->id_b))
        return;
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, h->id_h, b->id_b, d->id_b, distancia, h->speed, tempo + duracao); 
}

/* representa a morte de um heroi, liberando uma nova vaga e avisando o porteiro */
void morre(struct mundo_t *w, struct evento_t *ev){
    struct heroi_t *h = &w->vet_h[ev->info1];
    struct base_t *b = &w->vet_b[h->id_b];
    struct missao_t *m = &w->vet_m[ev->info2];
    int tempo = ev->tempo;
    /* se o heroi ja esta morto o evento nao ocorre, ou se nao houver presentes naquela base para que alguem morra */
    if (!verifica_mundo(w) || !b->presentes || h->morto) 
        return;
    printf("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, h->id_h, m->id_m);
    if (cjto_retira(b->presentes, h->id_h) < 0){
        printf("Erro: o heroi %d nao foi removido da lista de presentes da base %d\n", h->id_h, h->id_b);
        return;
    }
    h->morto = true;
    w->mortes++; /* incrementa a quantidade de mortes */
    if (!adiciona_evento(w, tempo, AVISA, -1, b->id_b))
        return;    
}

/* une todas as habilidades dos herois de uma mesma base */
/* verifica se o heroi esta naquela base e, se sim, adiciona suas habilidades ao conjunto */
struct cjto_t *skills_b(struct mundo_t *w, int id_b){
    if (!verifica_mundo(w))
        return NULL;
    struct cjto_t *uniao = cjto_cria(N_HABILIDADES); /* cria um conjunto vazio com capacidade para ate N_HABILIDADES */
    if (!uniao){
        printf("Erro: o conjunto de habilidades nao foi criado\n");
        return NULL;
    }
    struct base_t *b = &w->vet_b[id_b];
    
    for (int i = 0; i < w->qtd_h; i++){
        if (cjto_pertence(b->presentes, i)){
            struct cjto_t *antigo = uniao; /* precisa guardar o conjunto antigo de habilidades para nao ser perdido */
            uniao = cjto_uniao(antigo, (w->vet_h[i]).skills);
            cjto_destroi(antigo);
        }
    }    
    return uniao;
}

/* encontra o id do heroi com maior qtd de experiencia em uma base de id igual a id_b */
int maior_xp(struct mundo_t *w, int id_b){
    if (!verifica_mundo(w))
        return -1;
    int maior = -1;
    int maior_id = -1;
    for (int i = 0; i < w->qtd_h; i++){
        if (cjto_pertence(w->vet_b[id_b].presentes, i)){
            if ((w->vet_h[i]).exp > maior){
                maior = (w->vet_h[i]).exp;
                maior_id = (w->vet_h[i]).id_h;
            }
        }

    }
    return maior_id;

}

/* representa o disparo de uma missao nova no instante T*/
void evento_missao(struct mundo_t *w, struct evento_t *ev){
    struct missao_t *m = &w->vet_m[ev->info1];
    struct dist_base dist[N_BASES]; /* struct de distancia de cada base ate a missao */
    int tempo = ev->tempo;    
    if (!verifica_mundo(w) || m->realizou)
        return;
    m->tentativas++;
    /* verifica a distancia de cada base em relacao ao local da missao */
    for (int i = 0; i < N_BASES; i++){
        dist[i].id = i;
        dist[i].distancia = dist_coord(m->local, (w->vet_b[i]).local);
    }
    ordena_dist(dist, N_BASES);
    int base_missao = -1;

    for (int i = 0; i < N_BASES; i++){
        /* prints de depuracao do evento missao */
        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", tempo, m->id_m, i, dist[i].distancia);
        cjto_imprime(w->vet_b[i].presentes);
        printf(" ]\n");
        for (int j = 0; j < N_HEROIS; j++){
            if (cjto_pertence(w->vet_b[i].presentes, j)){
                printf(" %6d: MISSAO %d HAB HEROI %2d: [ ", tempo, m->id_m, j);
                cjto_imprime(w->vet_h[j].skills);
                printf(" ]\n");
            }
        }
        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", tempo, m->id_m, i);
        cjto_imprime(skills_b(w, i));
        printf(" ]\n"); 
    }    
    
    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", tempo, m->id_m, m->tentativas);
    cjto_imprime(m->skills);
    printf(" ]\n");

    /* verifica se o cjto de habilidades de uma base de id igual a i possui as habilidades */
    /* necessarias para essa missao e, se sim, aquela sera a base da missao */
    for (int i = 0; i < w->qtd_b; i++){
        struct cjto_t *uni = skills_b(w, dist[i].id);
        if (cjto_contem(uni, m->skills)){
            base_missao = dist[i].id;
        }
        cjto_destroi(uni); /* destroi o cjto uniao usado para agrupar as habilidades dos herois da base */
    }

    if (base_missao >= 0){
        m->realizou = true;
        (w->vet_b[base_missao]).missoes++;
        w->missoes_cumpridas++;
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, m->id_m, base_missao);
        cjto_imprime((w->vet_b[base_missao]).presentes);
        printf(" ]\n");
        /* aumentar xp dos herois */
        for (int j = 0; j < w->qtd_h; j++){
            if (cjto_pertence(w->vet_b[base_missao].presentes, j))
                (w->vet_h[j]).exp++;
        }
        return;
    }
    /* usar Composto V na base mais próxima (dist[0].id) */
    if ((w->qtd_v > 0) && (tempo % 2500 == 0)){
        int b_proxima = dist[0].id; /* pega a base mais perto da missao */
        int heroi_sacrificado = maior_xp(w, b_proxima); /* procura heroi nela */
        if (heroi_sacrificado != -1) { /* consome se tiver um heroi para usar */
            w->qtd_v--;
            m->realizou = true;
            w->vet_b[b_proxima].missoes++;
            w->missoes_cumpridas++; /* missao cumprida */
            /* agenda a morte do heroi */
            adiciona_evento(w, tempo, MORRE, heroi_sacrificado, m->id_m);
            for (int j = 0; j < w->qtd_h; j++){
                if (cjto_pertence(w->vet_b[b_proxima].presentes, j))
                    (w->vet_h[j]).exp++;
            }
            printf("%6d: MISSAO %d CUMPRIDA BASE %d COMPOSTO V HEROI %d\n", tempo, m->id_m, b_proxima, heroi_sacrificado);
            return;
        }
    }
    /* isso so ocorre se nao tiver achado a base ou usado um composto v */
    printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, m->id_m); 
    /* coloca na agenda de novo */
    if (!adiciona_evento(w, tempo + 24*60, MISSAO, m->id_m, -1))
        return;
}

/* retorna o tempo atual do mundo */
int tempo_mundo(struct mundo_t *w){
    return w->tempo;
}

/* representa o fim da simulacao */
void ev_fim(struct mundo_t *w){
    if (!verifica_mundo(w))
        return;

    printf("%6d: FIM\n", T_FIM_DO_MUNDO);
    for (int i = 0; i < N_HEROIS; i++){
        struct heroi_t *h = &w->vet_h[i];
        if (h->morto)
            printf("HEROI %2d MORTO ", i);
        else
            printf("HEROI %2d VIVO ", i);
        printf("PAC %3d VEL %4d EXP %4d HABS [ ", h->paciencia, h->speed, h->exp);
        cjto_imprime(h->skills);
        printf(" ]\n");
    }

    for (int i = 0; i < N_BASES; i++){
        struct base_t *base = &w->vet_b[i];
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", i, base->limite, base->max_fila, base->missoes);
    }
    float taxa_missoes = ((float)w->missoes_cumpridas / N_MISSOES) * 1000000.0;
    printf("EVENTOS TRATADOS: %d\n", w->total_eventos);
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", w->missoes_cumpridas, N_MISSOES, taxa_missoes);
    int max_tentativas = 0;
    /* encontra a missao com o maior numero de tentativas */
    for (int a = 0; a < w->qtd_m; a++){
        if (((w->vet_m[a]).tentativas) > max_tentativas)
            max_tentativas = (w->vet_m[a]).tentativas;
    }
    int min_tentativas = max_tentativas; /* inicializa com o maximo para garantir que ira encontrar o menor num de tentativas */
    for (int a = 0; a < w->qtd_m; a++){
            if ((w->vet_m[a]).tentativas < min_tentativas && (w->vet_m[a]).tentativas > 0)
                min_tentativas = (w->vet_m[a]).tentativas;
    }
    int soma = 0;
    for (int a = 0; a < w->qtd_m; a++){
        soma = soma + (w->vet_m[a]).tentativas;
    }            
    float media = (float)soma/w->qtd_m; /* soma de todas as tentativas dividida pela qtd de missoes */
    float mortalidade =  ((float)w->mortes / w->qtd_h) * 100.0;
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_tentativas, max_tentativas, media);
    printf("TAXA MORTALIDADE: %.1f%%\n", mortalidade);
}

/* inicia a simulacao dos eventos do mundo */
void simula_eventos(struct mundo_t *w){
    struct evento_t *ev;
    int tipo_evento, tempo, fim = 0;
    if (!verifica_mundo(w))
        return;
    /* o mundo nao pode ter chegado ao fim e nem a lef vazia */
    /* pois isso significaria que ela nao tem mais eventos */
    while (!fim && fprio_tamanho(w->lef) > 0){
        ev = fprio_retira(w->lef, &tipo_evento, &tempo);
        if (!ev)
            break;
        /* exceto os eventos que nao envolvem diretamente herois, eh preciso testar */
        /* se o heroi nao esta morto, pois dessa forma nao conseguiria fazer a missao */
        if ((tipo_evento != MISSAO) && (tipo_evento != AVISA) && (tipo_evento != FIM)){
            struct heroi_t *h = &w->vet_h[ev->info1];
            if (h->morto){
                free(ev);
                printf("Erro: o heroi %d ja morreu\n", ev->info1);
                continue; /* termina o loop antes porque esse evento nao pode acontecer */
            }
        }
        w->tempo = tempo;
        w->total_eventos++;
                
        switch(tipo_evento){        
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
                evento_missao(w, ev);
                break;
            case FIM:
                ev_fim(w);
                fim = 1;
        }
        free(ev);
    }
}
