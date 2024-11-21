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

int inicia_eventos(struct mundo_t *m, struct fprio_t *lef);

int add_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2);

void chega(int tempo, struct ev_hb *e, struct mundo_t *m);

void espera(int tempo, struct ev_hb *e, struct mundo_t *m);

void desiste(int tempo, struct ev_hb *e, struct mundo_t *m);

void avisa(int tempo, struct ev_b *e, struct mundo_t *m);

void entra(int tempo, struct ev_hb *e, struct mundo_t *m);

void sai(int tempo, struct ev_hb *e, struct mundo_t *m);

void viaja(int tempo, struct ev_hb *e, struct mundo_t *m);

void morre(int tempo, struct ev_hm *e, struct mundo_t *m);

void missao(int tempo, struct ev_m *e, struct mundo_t *m);

void fim(int tempo);

int simular_eventos(struct mundo_t *m, struct fprio_t *lef);

#endif
