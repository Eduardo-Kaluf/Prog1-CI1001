
#include "theboys.h"
#include "eventos.h"
#include "fprio.h"
#include "fila.h"
#include "utils.h"

#include <stdio.h>


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

int simular_eventos(struct mundo_t *m, struct fprio_t *lef) {
    struct evento *e;
    int evento_id;
    int tempo;

    while ((e = (struct evento *) fprio_retira(lef, &evento_id, &tempo))) {
        switch (evento_id) {
        case EV_CHEGA:
            printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", 
                tempo,
                e->info1,
                e->info2,
                m->bases[e->info2].presentes->num,
                m->bases[e->info2].lotacao
            );
            
            chega(tempo, e, m);
            break;
        case EV_ESPERA:

            espera(tempo, e, m);
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

int add_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2) {
    struct evento *e;
        
    if (!(e = malloc(sizeof(struct evento))))
        return 0;
    
    e->info1 = info1;
    e->info2 = info2;

    fprio_insere(m->lef, e, tipo, tempo);

    return 1;
}

void chega(int tempo, struct evento *e, struct mundo_t *m) {
    int espera;
    struct heroi_t h = m->herois[e->info1];
    struct base_t b = m->bases[e->info2];

    if (b.presentes->num != b.lotacao && b.espera->tamanho == 0)
        espera = 1;
    else
        espera = (h.paciencia > (10 * b.espera->tamanho));

    if (espera) {
        add_evento(m, EV_ESPERA, tempo, h.id, b.id);
        printf("ESPERA\n");
    }
    else {
        add_evento(m, EV_DESISTE, tempo, h.id, b.id);
        printf("DESISTE\n");
    }

    return;
}

// Devo usar h.id ou e->info1?
void espera(int tempo, struct evento *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->info1];
    struct base_t b = m->bases[e->info2];
    
    enqueue(b.espera, h.id);
    add_evento(m, EV_AVISA, tempo, b.id, -1);

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
        tempo,
        h.id,
        b.id,
        b.espera->tamanho);

}

void desiste(int tempo, struct evento *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->info1];
    struct base_t b = m->bases[e->info2];
    
    int base_dest = aleat(0, N_BASES - 1);

    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);

    printf("%6d: DESISTE HEROI %2d BASE %d\n",
        tempo,
        h.id,
        b.id);

}

void avisa(int tempo, struct evento *e, struct mundo_t *m) {
    struct base_t b = m->bases[e->info1];
    int *h_id;
    
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
        tempo,
        b.id,
        b.espera->tamanho,
        b.lotacao
    );
    
    fila_imprime(b.espera);
    
    while (b.espera->tamanho != 0 && b.presentes->num != b.lotacao) {

        dequeue(b.espera, h_id);
        cjto_insere(b.presentes, h_id);
        add_evento(m, EV_ENTRA, tempo, h_id, b.id);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", 
            tempo,
            b.id,
            h_id);
    }
}

void entra(int tempo, struct evento *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->info1];
    struct base_t b = m->bases[e->info2];

    int tpb = 15 + h.paciencia * aleat(0, 20);

    add_evento(m, EV_SAI, tempo + tpb, h.id, b.id);

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
        tempo,
        h.id,
        b.id,
        b.espera->tamanho + 1,
        b.lotacao,
        tpb);
    
    return;
}

void sai(int tempo, struct evento *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->info1];
    struct base_t b = m->bases[e->info2];
    
    cjto_retira(b.presentes, b.id);
    int base_dest = aleat(0, N_BASES - 1);
    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);
    add_evento(m, EV_AVISA, tempo, b.id, -1);

    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
        tempo,
        h.id,
        b.id,
        b.espera->tamanho - 1,
        b.lotacao);

    return;
}

void viaja(int tempo, struct evento *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->info1];
    struct base_t b = m->bases[e->info2];

    // calcula duração da viagem:
    //     distância = distância cartesiana entre a base atual de H e a base D 
    //     duração = distância / velocidade de H
    // cria e insere na LEF o evento CHEGA (agora + duração, H, D)

    return;
}

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

