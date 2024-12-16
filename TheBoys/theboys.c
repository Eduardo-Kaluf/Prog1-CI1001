/* 
 * Trabalho: TheBoys
 * Autor: Eduardo Kaluf, GRR 20241770
 * Programa principal
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#include <stdlib.h>
#include <stdio.h>

#include "fila.h"
#include "utils.h"
#include "theboys.h"
#include "fprio.h"
#include "eventos.h"

int inicia_mundo(struct mundo_t *m) {

    m->n_herois = N_HEROIS;
    m->n_bases = N_BASES;
    m->n_missoes = N_MISSOES;
    m->n_habilidades = N_HABILIDADES;
    m->tamanho_mundo = cria_coordenada(N_TAMANHO_MUNDO, N_TAMANHO_MUNDO);
    m->relogio = T_INICIO;
    m->mortes = 0;
    m->lef = fprio_cria();
    m->missoes_cumpridas = 0;
    m->ev_processados = 0;
    m->max_tentativas = 0;
    m->min_tentativas = 0;
    m->tentativas = 0;

    return 1;
}

int inicia_herois(struct heroi_t herois[]) {
    
    for (int i = 0; i < N_HEROIS; i++) {
        herois[i].id = i;
        herois[i].experiencia = 0;
        herois[i].paciencia = aleat(0, 100);
        herois[i].velocidade  = aleat(50, 5000);
        herois[i].base_id = H_BASE_INI;
        herois[i].morto = 0;
        if (!(herois[i].habilidades = cjto_aleat(aleat(1, 3), N_HABILIDADES)))
            return 0;
    }   
    
    return 1;
}

int inicia_bases(struct base_t bases[]) {

    for (int i = 0; i < N_BASES; i++) {
        bases[i].id = i;
        bases[i].participacao = 0;
        bases[i].local = cria_coordenada(aleat(0, N_TAMANHO_MUNDO - 1), 
                                         aleat(0, N_TAMANHO_MUNDO - 1));
        bases[i].lotacao = aleat(B_LOTACAO_MIN, B_LOTACAO_MAX);
        bases[i].espera = fila_cria();
        if (!(bases[i].presentes = cjto_cria(N_HEROIS)))
            return 0;
    }

    return 1;
}

int inicia_missoes(struct missao_t missoes[]) {

    for (int i = 0; i < N_MISSOES; i++) {
        missoes[i].cumprida = 0;
        missoes[i].id = i;
        missoes[i].tentativa = 0;
        missoes[i].perigo = aleat(0, 100);
        missoes[i].local = cria_coordenada(aleat(0, N_TAMANHO_MUNDO - 1), 
                                           aleat(0, N_TAMANHO_MUNDO - 1));
        if (!(missoes[i].habilidades = cjto_aleat(aleat(6, 10), N_HABILIDADES)))
            return 0;
    }

    return 1;
}

void destroi_herois(struct heroi_t herois[]) {
    for (int i = 0; i < N_HEROIS; i++) {
        if (herois[i].habilidades != NULL)
            cjto_destroi(herois[i].habilidades);
    }
}

void destroi_bases(struct base_t bases[]) {
    for (int i = 0; i < N_BASES; i++) {
        if (bases[i].presentes != NULL)
            cjto_destroi(bases[i].presentes);
        if (bases[i].espera != NULL)
            fila_destroi(bases[i].espera);
    }
}

void destroi_missoes(struct missao_t missoes[]) {
    for (int i = 0; i < N_MISSOES; i++) {
        if (missoes[i].habilidades != NULL)
            cjto_destroi(missoes[i].habilidades);
    }
}

int main () {
    srand(6);
 
    struct mundo_t m;
    
    inicia_mundo(&m);

    if (!(inicia_herois(m.herois))) {
        printf("Erro ao inicializar herois");
        return 1;
    }
    
    if (!(inicia_bases(m.bases))) {
        printf("Erro ao inicializar bases");
        return 1;
    }

    if (!(inicia_missoes(m.missoes))) {
        printf("Erro ao inicializar missões");
        return 1;
    }

    if (!(inicia_eventos(&m))) {
        printf("Erro ao inicializar eventos");
        return 1;
    }

    simular_eventos(&m);
    
    destroi_herois(m.herois);
    destroi_bases(m.bases);
    destroi_missoes(m.missoes);

    fprio_destroi(m.lef);

    return 0;
}
