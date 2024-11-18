#ifndef EVENTOS
#define EVENTOS

#include "theboys.h"
#include "fprio.h"

struct evento {
    int info1;
    int info2;
};


/*
 * Eventos iniciais
*/

int inicia_eventos(struct mundo_t *m, struct fprio_t *lef);

int add_evento(struct mundo_t *m, int tipo, int tempo, int info1, int info2);

void chega(int tempo, struct evento *e, struct mundo_t *m);

void espera(int tempo, struct evento *e, struct mundo_t *m);

void desiste(int tempo, struct evento *e, struct mundo_t *m);

void avisa(int tempo, struct base_t b);

void entra(int tempo, struct evento *e, struct mundo_t *m);

void sai(int tempo, struct evento *e, struct mundo_t *m);

void viaja(int tempo, struct evento *e, struct mundo_t *m);

void morre(int tempo, struct evento *e, struct mundo_t *m);

void missao(int tempo, struct missao_t m);

void fim(int tempo);

int simular_eventos(struct mundo_t *m, struct fprio_t *lef);

#endif
