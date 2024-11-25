/* 
 * Trabalho: TheBoys
 * Arquivo header usado para defines, structs e funções essenciais do projeto
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

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

#define B_LOTACAO_MAX    10
#define B_LOTACAO_MIN    3

#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_MORRE 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_AVISA 8
#define EV_MISSAO 9
#define EV_FIM 10

struct heroi_t {
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base_id;
    int morto;
};

struct base_t {
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct coordenada_t local;
    int participacao;
};

struct missao_t {
    int id;
    struct cjto_t *habilidades;
    int perigo;
    struct coordenada_t local;
    int tentativa;
    int cumprida;
};

struct mundo_t {
    int n_herois;
    struct heroi_t herois[N_HEROIS];
    int n_bases;
    struct base_t bases[N_BASES];
    int n_missoes;
    struct missao_t missoes[N_MISSOES];
    int n_habilidades;
    struct coordenada_t tamanho_mundo;
    int relogio;
    int mortes;
    struct fprio_t *lef;
    int missoes_cumpridas;
    int ev_processados;
    int max_tentativas;
    int min_tentativas;
    int tentativas;
};

int inicia_mundo (struct mundo_t *m);

int inicia_herois (struct heroi_t herois[]);

int inicia_bases (struct base_t bases[]);

int inicia_missoes (struct missao_t missoes[]);

void destroi_herois (struct heroi_t herois[]);

void destroi_bases (struct base_t bases[]);

void destroi_missoes (struct missao_t missoes[]);

#endif
