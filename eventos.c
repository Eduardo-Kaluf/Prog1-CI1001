
#include "theboys.h"
#include "eventos.h"
#include "fprio.h"
#include "fila.h"
#include "utils.h"

#include <stdio.h>

// TODO: TROCAR AS OPERAÇÕES DO CONJUNTO (EXEMPLO CNJT.NUM TROCAR PAR CJNT_CARDINALIDADE())


// TODO: RETIRAR "evento"
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

    while ((e = fprio_retira(lef, &evento_id, &tempo))) {
        switch (evento_id) {
        case EV_CHEGA:
            chega(tempo, (struct ev_hb *) e, m);
            break;
        case EV_ESPERA:

            espera(tempo, (struct ev_hb *) e, m);
            break;
        case EV_DESISTE:

            desiste(tempo, (struct ev_hb *) e, m);
            break;
        case EV_AVISA:
        
            avisa(tempo, (struct ev_b *) e, m);
            break;
        case EV_ENTRA:
        
            entra(tempo, (struct ev_hb *) e, m);
            break;
        case EV_SAI:
            
            sai(tempo, (struct ev_hb *) e, m);
            break;
        case EV_VIAJA:

            viaja(tempo, (struct ev_hb *) e, m);
            break;
        case EV_MORRE:
            break;
        case EV_MISSAO:
            break;
        case EV_FIM:
            fim(tempo);
            return 0;
        }

    }

    return 1;
}

// TODO: VER SE É POSSIVEL UTILZIAR evento COMO UMA STRUCT GENÉRICA OU SE PRECISO USAR AS ESPECIFICAS
int add_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2) {
    struct evento *e;
        
    if (!(e = malloc(sizeof(struct evento))))
        return 0;
    
    e->info1 = info1;
    e->info2 = info2;

    fprio_insere(m->lef, e, tipo, tempo);

    return 1;
}

void chega(int tempo, struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int espera;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", 
        tempo,
        h.id,
        b.id,
        cjto_card(b.presentes),
        b.lotacao
    );

    // ATUALIZA A BASE DO HEROI EM SI E NÃO A CÓPIA !!!
    //h.base_id = b.id;
    m->herois[e->h_id].base_id = b.id;

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
void espera(int tempo, struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
        tempo,
        h.id,
        b.id,
        fila_tamanho(b.espera));

    enqueue(b.espera, h.id);
    add_evento(m, EV_AVISA, tempo, b.id, -1);
}

void desiste(int tempo,struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    
    int base_dest = aleat(0, N_BASES - 1);

    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);

    printf("%6d: DESISTE HEROI %2d BASE %d\n",
        tempo,
        h.id,
        b.id);

}

void avisa(int tempo, struct ev_b *e, struct mundo_t *m) {
    struct base_t b = m->bases[e->b_id];
    int h_id;
    
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
        tempo,
        b.id,
        cjto_card(b.presentes),
        b.lotacao
    );
    
    fila_imprime(b.espera);

    while (b.espera->tamanho != 0 && b.presentes->num != b.lotacao) {
        
        dequeue(b.espera, &h_id); 
        cjto_insere(b.presentes, h_id);
        add_evento(m, EV_ENTRA, tempo, h_id, b.id);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", 
           tempo,
           b.id,
           h_id);
    }

    
}

void entra(int tempo, struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];

    int tpb = 15 + h.paciencia * aleat(0, 20);
        
    cjto_imprime(b.presentes);
    printf("BASEAAAA\n");

    add_evento(m, EV_SAI, tempo + tpb, h.id, b.id);

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
        tempo,
        h.id,
        b.id,
        cjto_card(b.presentes),
        b.lotacao,
        tempo + tpb);
    
    return;
}

void sai(int tempo, struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    
    cjto_retira(b.presentes, b.id);
    int base_dest = aleat(0, N_BASES - 1);
    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);
    add_evento(m, EV_AVISA, tempo, b.id, -1);
    
    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
        tempo,
        h.id,
        b.id,
        cjto_card(b.presentes),
        b.lotacao);

    return;
}

void viaja(int tempo, struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int duracao, distancia;

    // TODO VERIFICAR CAST
    printf("ATENÇÃO %d\n", h.base_id);
    distancia = (int) d_cartesiana(m->bases[h.base_id].local, b.local);
    duracao = (distancia / h.velocidade);

    add_evento(m, EV_CHEGA, tempo + duracao, h.id, b.id);

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
        tempo,
        h.id,
        h.base_id,
        b.id,
        distancia,
        h.velocidade,
        tempo + duracao); 


    return;
}

void morre(int tempo, struct ev_hm *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[h.base_id];

    printf("%6d: MORRE  HEROI %2d MISSAO %d\n",
        tempo,
        h.id,
        e->m_id); 

    cjto_retira(b.presentes, h.id);

    // TODO ATUALIZAR O HEROI NO MUNDO E NÃO A CÓPIA
    // id = -1 implica que o herói está morto
    //h.id = -1;
    // h.base_id = -1;

    add_evento(m, EV_AVISA, tempo, b.id, -1);

    return;
}

void missao(int tempo, struct ev_m *e, struct mundo_t *m) {
    struct missao_t mi = m->missoes[e->m_id];
    struct dist_base distancias[N_BASES];
    struct base_t b; 

    for (int i = 0; i < N_BASES; i++) {
        distancias[i] = (struct dist_base) {
            .id = i,
            .distancia = d_cartesiana(mi.local, m->bases[i].local)
        };
    }

    // ShellSort utilizando a sequência de Knuth
    ordena_dist_bases(distancias, N_BASES);

    //TODO REMOVER DPS
    for (int i = 0; i < N_BASES; i++) {
        printf("%d", distancias[i].distancia);
    }


    // TODO VERIFICAR ESSA UNIÃO


    for (int i = 0; i < N_BASES; i++) {
        b = m->bases[distancias[i].id];
        struct heroi_t h[b.presentes->num];
        int risco;
        struct cjto_t *uniao = cjto_cria(cjto_card(mi.habilidades));
        
        for (int i = 0; i < N_HEROIS; i++) {
            if (cjto_pertence(b.presentes, m->herois[i].id))
                uniao = cjto_uniao(uniao, m->herois[i].habilidades);
        }

        if (cjto_contem(uniao, mi.habilidades)) {
            // MISSAO CUMPRIDA
            mi.id = -1;
            // TODO VERIFICAR SE O NUMERO DE HEROIS QUE VÃO PARA A MISSÃO
            // TODO É O MESMO NUMERO DE HEROIS PRESENTES NA BASE 
            for (int i = 0; i < b.presentes->num; i++) {
                risco = mi.perigo / (h[i].paciencia + h->experiencia + 1.0);
                if (risco > aleat(0, 30))
                    add_evento(m, EV_MORRE, tempo, h->id, -1);
                else
                    h->experiencia += 1;
            }
        }
        // VERIFICAR ESSE ELSE
        else
            add_evento(m, EV_MISSAO, tempo + 24*60, mi.id, -1);
    }

    return;
}

// se houver uma BMP:
//     marca a missão M como cumprida
//     para cada herói H presente na BMP:
//         risco = perigo (M) / (paciência (H) + experiência (H) + 1.0)
//         se risco > aleatório (0, 30):
//             cria e insere na LEF o evento MORRE (agora, H)
//         senão:
//             incrementa a experiência de H

void fim(int tempo) {
    printf("ESTATISTICAS: %d\n", tempo);
    
    return;
}

