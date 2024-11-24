/* 
 * Trabalho: TheBoys
 * Arquivo de implementação para as funções de eventos
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#include "theboys.h"
#include "eventos.h"
#include "fprio.h"
#include "fila.h"
#include "utils.h"

#include <stdio.h>

// TODO: TROCAR AS OPERAÇÕES DO CONJUNTO (EXEMPLO CNJT.NUM TROCAR PAR CJNT_CARDINALIDADE())

// TODO: VER EM QUAIS SITUAÇÕES DEVO CHEGAR SE O HERÓI ESTÁ MORTO 
// TODO: POSSIVELMENTE ADICIONAR UM "MORTOS" NO MUNDO, PARA MANTER TRACKING DE QUANTOS HEROIS MORRERAM

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

            missao(tempo, (struct ev_m *) e, m);
            break;
        case EV_FIM:
            
            fim(tempo);
            free(e);
            return 1;
        }

        free(e);

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

    // Atualiza o herói que pertence ao mundo e não a cópia
    m->herois[e->h_id].base_id = b.id;

    if (cjto_card(b.presentes) != b.lotacao && fila_tamanho(b.espera) == 0)
        espera = 1;
    else
        espera = (h.paciencia > (10 * fila_tamanho(b.espera)));

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

    return;
}

void desiste(int tempo,struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int base_dest;

    printf("%6d: DESISTE HEROI %2d BASE %d\n",
        tempo,
        h.id,
        b.id);

    base_dest = aleat(0, N_BASES - 1);

    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);

    return;
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

    while (!fila_vazia(b.espera) && cjto_card(b.presentes) != b.lotacao) {
        
        dequeue(b.espera, &h_id);
        cjto_insere(b.presentes, h_id);
        add_evento(m, EV_ENTRA, tempo, h_id, b.id);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", 
           tempo,
           b.id,
           h_id);
    }

    return;
}

void entra(int tempo, struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int tpb;

    tpb = 15 + h.paciencia * aleat(1, 20);
        
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
    int base_dest;

    base_dest = aleat(0, N_BASES - 1);
    
    cjto_retira(b.presentes, h.id);

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

    distancia = (int) d_cartesiana(m->bases[h.base_id].local, b.local);
    duracao = distancia / h.velocidade;

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

    // id = -1 implica que o herói está morto
    m->herois[e->h_id].id = -1;

    add_evento(m, EV_AVISA, tempo, b.id, -1);

    return;
}

// TODO FINALIZAR MISSAO
void missao(int tempo, struct ev_m *e, struct mundo_t *m) {
    m->missoes[e->m_id].tentativa += 1;
    struct missao_t mi = m->missoes[e->m_id];
    struct dist_base distancias[N_BASES];
    struct base_t b; 
    int bmp = 0;
    struct cjto_t *uni;
    int risco;
    // 10 é o número máximo de heróis presentes em uma base
    int herois[10];



    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", 
        tempo,
        mi.id,
        mi.tentativa);
    
    cjto_imprime(mi.habilidades);

    printf(" ]\n");

    for (int i = 0; i < N_BASES; i++) {
        distancias[i] = (struct dist_base) {
            .id = i,
            .distancia = d_cartesiana(mi.local, m->bases[i].local)
        };
    }

    // ShellSort utilizando a sequência de Knuth
    ordena_distancias(distancias, N_BASES);
    
    for (int i = 0; i < N_BASES; i++) {
        b = m->bases[distancias[i].id];
        int j = 0;
        uni = cjto_cria(cjto_card(mi.habilidades));
        
        for (int i = 0; i < N_HEROIS; i++) {
            if (b.presentes->flag[i] == 1) {
                herois[j] = i;
                j++;
            }
        }

        for (int i = 0; i < cjto_card(b.presentes); i++) {
            uni = cjto_uniao(uni, m->herois[herois[i]].habilidades);
        }

        if (cjto_contem(uni, mi.habilidades)) {
            bmp = 1;
            break;
        }
    }

    if (bmp) {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",
            tempo,
            mi.id,
            b.id);

        cjto_imprime(uni);
        printf(" ]\n"); 

        mi.id = -1;

        for (int i = 0; i < cjto_card(b.presentes); i++) {
            risco = mi.perigo / (m->herois[herois[i]].paciencia + m->herois[herois[i]].experiencia + 1.0);
            if (risco > aleat(0, 30))
                add_evento(m, EV_MORRE, tempo, herois[i], -1);
            else
                m->herois[herois[i]].experiencia += 1;
        }
    }
    else {
        printf("%6d: MISSAO %d IMPOSSIVEL\n",
            tempo,
            mi.id);
        add_evento(m, EV_MISSAO, tempo + 24*60, mi.id, -1);
    }

    return;
}

void fim(int tempo) {
    printf("ESTATISTICAS: %d\n", tempo);
    
    return;
}

