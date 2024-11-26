/* 
 * Trabalho: TheBoys
 * Arquivo header para as funções de eventos
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#ifndef EVENTOS
#define EVENTOS

#include "theboys.h"
#include "fprio.h"

// Representa um evento que utiliza "Herói" e "Base"
struct ev_hb {
    int h_id;
    int b_id;
};

// Representa um evento que utiliza apenas "Base"
struct ev_b {
    int b_id;
};

// Representa um evento que utiliza "Herói" e "Missão"
struct ev_hm {
    int h_id;
    int mi_id;
};

// Representa um evento que utiliza apenas "Missão"
struct ev_m {
    int mi_id;
};

// Representa um evento genérico
// Utilizado para inserir eventos na LEF
struct evento {
    int info1;
    int info2;
};


/* 
 * Inicia os primeiros eventos do mundo:
 *  - Chegada dos heróis
 *  - Agenda as missões
 *  - Agenda o fim do mundo
*/
int inicia_eventos (struct mundo_t *m);


/*
 * Atualiza as informações que se relacionam as missões
 * Que serão utilizadas para gerar o relatório no final do mundo.
*/
void att_ev_mi_info (struct mundo_t *m, int mi_id, int b_id, int bmp);

/*
 * Cria e adiciona um evento genérico na LEF
*/
int add_evento (struct mundo_t *m, int tipo, int tempo, int info1, int info2);

/*
 * Representa um herói chegando em uma base.
 *  - Ao chegar, o herói analisa o tamanho da fila e as vagas da base 
 *  - Então decide se ESPERA para entrar ou DESISTE
*/
void chega (struct ev_hb *e, struct mundo_t *m);

/*
 * O herói entra na fila de espera da base.
 * Assim que o herói entra na fila, AVISA o porteiro da base
*/
void espera (struct ev_hb *e, struct mundo_t *m);

/*
 *
*/
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
