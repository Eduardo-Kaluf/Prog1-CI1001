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
#include "logger.h"

int add_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2) {
    struct evento *e;
        
    if (!(e = malloc(sizeof(struct evento))))
        return 0;
    
    e->info1 = info1;
    e->info2 = info2;

    fprio_insere(m->lef, e, tipo, tempo);

    return 1;
}

void att_ev_mi_info(struct mundo_t *m, int mi_id, int b_id, int bmp) {
    struct missao_t mi;

    // Att a as tentativas do mundo e as da própria missão
    m->missoes[mi_id].tentativa += 1;
    m->tentativas += 1;
    
    /*
     *  Caso a missão tenha tido sucesso:
     *   - Marca-a como cumprida
     *   - Adiciona uma participação para a Base
     *   - Att as missões cumpridas do mundo
    */
    if (bmp) {
        m->missoes[mi_id].cumprida = 1;
        m->missoes_cumpridas += 1;
        m->bases[b_id].participacao += 1;
    }

    mi = m->missoes[mi_id];

    // Att o máximo de tentativas para realizar uma missão
    if (mi.tentativa > m->max_tentativas)
        m->max_tentativas = mi.tentativa;

    // Att o mínimo de tentativas para realizar uma missão
    if ((mi.tentativa < m->min_tentativas || m->min_tentativas == 0) && mi.cumprida == 1)
        m->min_tentativas = mi.tentativa;
}

int inicia_eventos(struct mundo_t *m) {
    int base, tempo; 

    // Chegada dos herois
    for (int i = 0; i < N_HEROIS; i++) {
        base = aleat(0, N_BASES - 1);
        tempo = aleat(0, 4320);
        if (!(add_evento(m, EV_CHEGA, tempo, m->herois[i].id, base)))
            return 0;
    }

    // Agenda as missões
    for (int i = 0; i < N_MISSOES; i++) {
        tempo = aleat(0, T_FIM_DO_MUNDO);
        if (!(add_evento(m, EV_MISSAO, tempo, m->missoes[i].id, -1)))
            return 0;
    }

    // Agenda o fim do mundo
    add_evento(m, EV_FIM, T_FIM_DO_MUNDO, -1, -1);

    return 1;
}

void simular_eventos(struct mundo_t *m) {
    struct evento *e;
    int evento_id, tempo, h_id;

    // Repete enquanto houver eventos na fila
    while ((e = fprio_retira(m->lef, &evento_id, &tempo))) {
        
        // Caso heroi esteja morto, ignora evento
        if (evento_id < EV_AVISA) {
            h_id = ((struct ev_hb *) e)->h_id;
            
            if (m->herois[h_id].morto) {
                free(e);
                continue;
            }
        }

        m->relogio = tempo;
        m->ev_processados += 1;

        // Seleciona o evento
        switch (evento_id) {
            case EV_CHEGA:

                chega((struct ev_hb *) e, m);
                break;
            case EV_ESPERA:

                espera((struct ev_hb *) e, m);
                break;
            case EV_DESISTE:

                desiste((struct ev_hb *) e, m);
                break;
            case EV_MORRE:

                morre((struct ev_hm *) e, m);
                break;
            case EV_ENTRA:
            
                entra((struct ev_hb *) e, m);
                break;
            case EV_SAI:
                
                sai((struct ev_hb *) e, m);
                break;
            case EV_VIAJA:

                viaja((struct ev_hb *) e, m);
                break;
            case EV_AVISA:
            
                avisa((struct ev_b *) e, m);
                break;
            case EV_MISSAO:

                missao((struct ev_m *) e, m);
                break;
            case EV_FIM:
                
                fim(m);
                free(e);
                return;
        }

        free(e);

    }
}

void chega(struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int espera, tempo = m->relogio;

    log_chega(tempo, h.id, b);

    // Atualiza o herói que pertence ao mundo e não a cópia
    m->herois[e->h_id].base_id = b.id;

    if (cjto_card(b.presentes) != b.lotacao && fila_tamanho(b.espera) == 0)
        espera = 1;
    else
        espera = (h.paciencia > (10 * fila_tamanho(b.espera)));

    if (espera) {
        log_chega_espera();
        add_evento(m, EV_ESPERA, tempo, h.id, b.id);
    }
    else {
        log_chega_desiste();
        add_evento(m, EV_DESISTE, tempo, h.id, b.id);
    }
}

void espera(struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int tempo = m->relogio;

    log_espera(tempo, h.id, b);

    enqueue(b.espera, h.id);

    add_evento(m, EV_AVISA, tempo, b.id, -1);
}

void desiste(struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int base_dest, tempo = m->relogio;

    log_desiste(tempo, h.id, b.id);

    base_dest = aleat(0, N_BASES - 1);

    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);
}

void morre(struct ev_hm *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[h.base_id];
    int tempo = m->relogio;

    log_morre(tempo, h.id, e->mi_id);

    cjto_retira(b.presentes, h.id);

    // Atualiza o herói que pertence ao mundo e não a cópia
    m->herois[e->h_id].morto = 1;
    m->mortes += 1;

    add_evento(m, EV_AVISA, tempo, b.id, -1);
}

void entra(struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int tpb, saida, tempo = m->relogio;

    tpb = 15 + h.paciencia * aleat(1, 20);
    saida = tempo + tpb;

    add_evento(m, EV_SAI, saida, h.id, b.id);

    log_entra(tempo, h.id, b, saida);
}

void sai(struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int base_dest, tempo = m->relogio;

    base_dest = aleat(0, N_BASES - 1);
    
    cjto_retira(b.presentes, h.id);

    add_evento(m, EV_VIAJA, tempo, h.id, base_dest);
    add_evento(m, EV_AVISA, tempo, b.id, -1);
    
    log_sai(tempo, h.id, b);
}

void viaja(struct ev_hb *e, struct mundo_t *m) {
    struct heroi_t h = m->herois[e->h_id];
    struct base_t b = m->bases[e->b_id];
    int duracao, distancia, chegada, tempo = m->relogio;

    distancia = (int) d_cartesiana(m->bases[h.base_id].local, b.local);
    duracao = distancia / h.velocidade;
    chegada = tempo + duracao;

    add_evento(m, EV_CHEGA, chegada, h.id, b.id);

    log_viaja(tempo, h, b.id, distancia, chegada);
}

void avisa(struct ev_b *e, struct mundo_t *m) {
    struct base_t b = m->bases[e->b_id];
    int h_id, tempo = m->relogio;
    
    log_avisa_fila(tempo, b);

    while (!fila_vazia(b.espera) && cjto_card(b.presentes) != b.lotacao) {
        
        dequeue(b.espera, &h_id);
        cjto_insere(b.presentes, h_id);
        add_evento(m, EV_ENTRA, tempo, h_id, b.id);

        log_avisa_admite(tempo, b.id, h_id);
    }
}

void missao(struct ev_m *e, struct mundo_t *m) {
    struct missao_t mi = m->missoes[e->mi_id];
    struct dist_base distancias[N_BASES];
    struct base_t b; 
    struct cjto_t *uni, *aux;
    int risco, j, bmp = 0, tempo = m->relogio;
    int herois[B_LOTACAO_MAX];

    mi.tentativa += 1;

    // Calcula a distância de cada base em relação a missão
    for (int i = 0; i < N_BASES; i++) {
        distancias[i] = (struct dist_base) {
            .id = i,
            .distancia = d_cartesiana(mi.local, m->bases[i].local)
        };
    }

    ordena_distancias(distancias, N_BASES);
    
    // Começa a analisar base por base
    for (int i = 0; i < N_BASES; i++) {
        b = m->bases[distancias[i].id];
        uni = cjto_cria(N_HABILIDADES);
        j = 0;
        
        // Descobre quais heróis estão presentes na base
        for (int i = 0; i < N_HEROIS; i++) {
            if (cjto_pertence(b.presentes, i)) {
                herois[j] = i;
                j++;
            }
        }

        // Uni as habilidades dos heróis
        for (int i = 0; i < cjto_card(b.presentes); i++) {
            aux = uni;
            uni = cjto_uniao(uni, m->herois[herois[i]].habilidades);
            cjto_destroi(aux);
        }

        // Verifica se eles conseguem realizar a missão
        if (cjto_contem(uni, mi.habilidades)) {
            bmp = 1;
            break;
        }

        cjto_destroi(uni);
    }

    // Atualiza as informações relacionadas a essa missão
    att_ev_mi_info(m, mi.id, b.id, bmp);

    log_missao_tentativa(tempo, mi);

    if (bmp) {
        log_missao_cumprida(tempo, mi.id, b.id, uni);

        // Verifica quais heróis morreram e quais obteram sucesso na missão
        for (int i = 0; i < cjto_card(b.presentes); i++) {
            risco = mi.perigo / (m->herois[herois[i]].paciencia 
                               + m->herois[herois[i]].experiencia + 1.0);

            if (risco > aleat(0, 30))
                add_evento(m, EV_MORRE, tempo, herois[i], mi.id);
            else
                m->herois[herois[i]].experiencia += 1;
        }

        cjto_destroi(uni);
    }
    else {
        log_missao_impossivel(tempo, mi.id);
        add_evento(m, EV_MISSAO, tempo + 24*60, mi.id, -1);
    }
}

void fim(struct mundo_t *m) {
    struct heroi_t h;

    log_fim(m);

    for (int i = 0; i < N_HEROIS; i++) {
        h = m->herois[i];

        if (h.morto)
            log_h_morto(h.id);
        else
            log_h_vivo(h.id);
    
        log_heroi_info(h);
    }
    
    for (int i = 0; i < N_BASES; i++) {
        log_fim_base(m->bases[i]);
    }

    log_statisticas(m);
}
