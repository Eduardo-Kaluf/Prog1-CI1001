#ifndef EVENTOS
#define EVENTOS

#include "theboys.h"
#include "fprio.h"

/*
 * Eventos iniciais
*/

int inicia_eventos(struct mundo_t *m, struct fprio_t *lef);

void chega(int tempo, struct heroi_t h, struct base_t b);

void espera(int tempo, struct heroi_t h, struct base_t b);

void desiste(int tempo, struct heroi_t h, struct base_t b);

void avisa(int tempo, struct base_t b);

void entra(int tempo, struct heroi_t h, struct base_t b);

void sai(int tempo, struct heroi_t h, struct base_t b);

void viaja(int tempo, struct heroi_t h, struct base_t b);

void morre(int tempo, struct heroi_t h, struct base_t b);

void missao(int tempo, struct missao_t m);

void fim(int tempo);

int simular_eventos(struct mundo_t *m, struct fprio_t *lef);

#endif
