
#include "theboys.h"
#include "eventos.h"
#include "fprio.h"
#include "fila.h"

#include <stdio.h>

struct evento {
    int info1;
    int info2;
};

int inicia_eventos(struct mundo_t *m, struct fprio_t *lef) {
    int base, tempo; 
    struct evento *it;

    // Chegada dos herois
    for (int i = 0; i < N_HEROIS; i++) {
        
        if (!(it = malloc(sizeof(struct evento))))
            return 0;
        
        base = aleat(0, N_BASES - 1);
        tempo = aleat(0, 4320);
        it->info1 = m->herois[i].id;
        it->info2 = base;
        fprio_insere(lef, it, EV_CHEGA, tempo);
    }

    // Agenda as missões
    for (int i = 0; i < N_MISSOES; i++) {
        if (!(it = malloc(sizeof(struct evento))))
            return 0;
        tempo = aleat(0, T_FIM_DO_MUNDO);
        it->info1 = m->missoes[i].id;
        fprio_insere(lef, it, EV_MISSAO, tempo);
    }

    // Agenda o fim do mundo
    if (!(it = malloc(sizeof(struct evento))))
        return 0;

    fprio_insere(lef, it, EV_FIM, T_FIM_DO_MUNDO);
    
    return 1;
}

void chega(int tempo, struct heroi_t h, struct base_t b) {
    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n", 
        tempo,
        h.id,
        b.id,
        b.presentes->num,
        b.lotacao
    );

    return;
}

void espera(int tempo, struct heroi_t h, struct base_t b) {
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
        tempo,
        h.id,
        b.id,
        b.espera->tamanho);

    return;
}

void desiste(int tempo, struct heroi_t h, struct base_t b) {
    printf("%6d: DESIST HEROI %2d BASE %d\n",
        tempo,
        h.id,
        b.id);

    return;
}

void avisa(int tempo, struct base_t b) {
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
        tempo,
        b.id,
        b.espera->tamanho,
        b.lotacao
    );
    
    fila_imprime(b.espera);
    printf("\n");
    
    int *valor;

    if (!(valor = malloc(sizeof(int))))
        return;

    while (b.espera->tamanho != b.lotacao) {
        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", 
            tempo,
            b.id,
            b.espera->prim->valor);
        
        dequeue(b.espera, valor);
        
    }
    

    return;
}

void entra(int tempo, struct heroi_t h, struct base_t b) {
    
    int t_saida = aleat(0, 10000);

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
        tempo,
        h.id,
        b.id,
        b.espera->tamanho + 1,
        b.lotacao,
        t_saida);
    
    return;
}

void sai(int tempo, struct heroi_t h, struct base_t b) {
    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
        tempo,
        h.id,
        b.id,
        b.espera->tamanho - 1,
        b.lotacao);
    
    return;
}

// void viaja(int tempo, struct heroi_t h, struct base_t b) {

//     return;
// }

// void morre(int tempo, struct heroi_t h, struct base_t b, struct missao_t m) {
//     return;
// }

// void missao(int tempo, struct missao_t m) {
//     return;
// }

void fim(int tempo) {
    printf("ESTATISTICAS: %d\n", tempo);
    
    return;
}

int simular_eventos(struct mundo_t *m, struct fprio_t *lef) {
    struct evento *e;
    int evento_id;
    int tempo;

    while ((e = (struct evento *) fprio_retira(lef, &evento_id, &tempo))) {
        switch (evento_id) {
        case EV_CHEGA:
            chega(tempo, m->herois[e->info1], m->bases[e->info2]);
            break;
        case EV_ESPERA:
            break;
        case EV_DESISTE:
            break;
        case EV_AVISA:
            break;
        case EV_ENTRA:
            break;
        case EV_SAI:
            break;
        case EV_VIAJA:
            break;
        case EV_MORRE:
            break;
        case EV_MISSAO:
            break;
        case EV_FIM:
            break;

        }

    }

    return 1;
}