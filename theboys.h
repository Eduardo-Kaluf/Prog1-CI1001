// Autor: Eduardo Kaluf, GRR 20241770

#ifndef THEBOYS
#define THEBOYS

#include <stdlib.h>

#include "conjunto.h"
#include "fila.h"
#include "utils.h"

#define T_INICIO         0
#define T_FIM_DO_MUNDO   525600
#define N_TAMANHO_MUNDO  20000
#define N_HABILIDADES    10
#define N_HEROIS         N_HABILIDADES * 5
#define N_BASES          N_HEROIS / 5
#define N_MISSOES        T_FIM_DO_MUNDO / 100

typedef struct heroi_t {
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base_id;
};


typedef struct coordenada_t {
    int x;
    int y;
};


typedef struct base_t {
    int id;
    int lotacao;
    struct cjto_t presentes;
    struct fila_t espera;
    struct coordenada_t local;
};

typedef struct missao_t {
    int id;
    struct cjto_t habilidades;
    int perigo;
    struct coordenada_t local;
};

typedef struct mundo_t {
    int n_herois;
    struct heroi_t herois[N_HEROIS];
    int n_bases;
    struct base_t bases[N_BASES];
    int n_missoes;
    struct missao_t missoes[N_MISSOES];
    int n_habilidades;
    struct coordenada_t tamanho_mundo;
    int relogio;
};

struct heroi_t *cria_heroi(mundo_t *m) {
    struct heroi_t *h;

    if (!(h = malloc(sizeof(struct heroi_t))))
        return NULL;

    h->id = m->n_herois;
    m->n_herois += 1;
    h->experiencia = 0;
    h->paciencia = aleat(0, 100);
    h->velocidade  = aleat(50, 5000);
    h->habilidades = cjto_aleat(N_HABILIDADES, 3);

    return h;
}

// TODO!
struct base_t *cria_base(struct mundo_t *m) {
    struct base_t *b;

    b->id = m->n_bases;
    m->n_bases += 1;
}

#endif
