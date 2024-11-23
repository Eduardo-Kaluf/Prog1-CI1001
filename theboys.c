// programa principal do projeto "The Boys - 2024/2"
// Autor: Eduardo Kaluf, GRR 20241770

#include "fila.h"
#include "utils.h"
#include "theboys.h"
#include "fprio.h"
#include "eventos.h"

#include <stdlib.h>
#include <stdio.h>

// TODO REVISAR A INICIALIZAÇÃO DOS HEROIS BASES E DOS EVENTOS!
int inicia_herois(struct heroi_t herois[]) {
    
    for (int i = 0; i < N_HEROIS; i++) {
        herois[i].id = i;
        herois[i].base_id = -1;
        herois[i].experiencia = 0;
        herois[i].paciencia = aleat(0, 100);
        herois[i].velocidade  = aleat(50, 5000);
        if (!(herois[i].habilidades = cjto_aleat(3, N_HABILIDADES)))
            return 0;
    }   
    
    return 1;
}

int inicia_bases(struct base_t bases[]) {

    for (int i = 0; i < N_BASES; i++) {
        bases[i].id = i;
        bases[i].local = cria_coordenada(aleat(0, N_TAMANHO_MUNDO - 1), 
                                         aleat(0, N_TAMANHO_MUNDO - 1));
        bases[i].lotacao = aleat(3, 10);
        bases[i].espera = fila_cria();
        if (!(bases[i].presentes = cjto_cria(N_HEROIS)))
            return 0;
    }

    return 1;
}

int inicia_missoes(struct missao_t missoes[]) {

    for (int i = 0; i < N_MISSOES; i++) {
        missoes[i].id = i;
        missoes[i].perigo = aleat(0, 100);
        missoes[i].local = cria_coordenada(aleat(0, N_TAMANHO_MUNDO - 1), 
                                           aleat(0, N_TAMANHO_MUNDO - 1));
        if (!(missoes[i].habilidades = cjto_aleat(N_HABILIDADES, aleat(6, 10))))
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

// programa principal
int main ()
{
    srand(0);
 
    struct fprio_t *lef = fprio_cria();
    struct mundo_t m;

    m.lef = lef;

    // iniciar o mundo

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

    // FAZER UM INICIA MUNDO

    if (!(inicia_eventos(&m, lef)))
        return 1;

    // fprio_imprime(lef);

    if (!(simular_eventos(&m, lef))) {
        printf("AAAAAA");
        return 1;
    }


    destroi_herois(m.herois);
    destroi_bases(m.bases);
    destroi_missoes(m.missoes);

    fprio_destroi(lef);

    printf("FIMFIMFIM");

    return (0) ;
}

