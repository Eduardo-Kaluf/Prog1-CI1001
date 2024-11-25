/* 
 * Trabalho: TheBoys
 * Arquivo header para as funções de eventos
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#ifndef EVENTOS
#define EVENTOS

#include "theboys.h"
#include "fprio.h"

struct ev_hb {
    int h_id;
    int b_id;
};

struct ev_b {
    int b_id;
};

struct ev_hm {
    int h_id;
    int m_id;
};

struct ev_m {
    int m_id;
};

struct evento {
    int info1;
    int info2;
};

/*
 * Eventos iniciais
*/

int inicia_eventos (struct mundo_t *m);

void att_ev_mi_info (struct mundo_t *m, int mi_id, int b_id, int bmp);

int add_evento (struct mundo_t *m, int tipo, int tempo, int info1, int info2);

void chega (struct ev_hb *e, struct mundo_t *m);

void espera (struct ev_hb *e, struct mundo_t *m);

void desiste (struct ev_hb *e, struct mundo_t *m);

void avisa (struct ev_b *e, struct mundo_t *m);

void entra (struct ev_hb *e, struct mundo_t *m);

void sai (struct ev_hb *e, struct mundo_t *m);

void viaja (struct ev_hb *e, struct mundo_t *m);

void morre (struct ev_hm *e, struct mundo_t *m);

void missao (struct ev_m *e, struct mundo_t *m);

void fim (struct mundo_t *m);

void simular_eventos (struct mundo_t *m);

#endif
