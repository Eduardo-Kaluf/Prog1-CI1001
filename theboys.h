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

// Definições gerais da simulação
#define T_INICIO         0
#define T_FIM_DO_MUNDO   525600
#define N_TAMANHO_MUNDO  20000
#define N_HABILIDADES    10
#define N_HEROIS         N_HABILIDADES * 5
#define N_BASES          N_HEROIS / 5
#define N_MISSOES        T_FIM_DO_MUNDO / 100

#define B_LOTACAO_MAX    10
#define B_LOTACAO_MIN    3

#define H_BASE_INI       -1

// IDs dos eventos
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

/*
 * Representa um Herói:
 *
 * ID: número inteiro que identifica unicamente o herói;
 * Habilidades: ponteiro para conjunto de habilidades que o herói possui. 
 *              Cada habilidade é representada por um número inteiro ≥ 0;
 * Paciência: número inteiro ≥ 0. Afeta as decisões de permanência em bases e ﬁlas;
 * Velocidade: número inteiro ≥ 0. Afeta o tempo de deslocamento entre as bases;
 * Experiência: número inteiro ≥ 0. Afeta a chance de um herói morrer em uma missão;
 * Base_id: ID da base onde o herói se encontra no momento.
 * Morto: 0 ou 1 indica se o Herói está morto (1) ou não (0);
*/
struct heroi_t {
    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base_id;
    int morto;
};

/*
 * Representa uma Base:
 *
 * ID: número inteiro ≥ 0 que identifica cada base;
 * Lotação: número máximo de heróis naquela base;
 * Presentes: ponteiro para conjunto dos IDs dos heróis que estão atualmente na base;
 * Espera: ponteiro para fila onde os heróis esperam para poder entrar na base;
 * Local: localização da base (coordenada inteira X, Y ≥ 0).
 * Participacao: quantidade de missões cumpridas que a Base participou;
*/
struct base_t {
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct coordenada_t local;
    int participacao;
};

/*
 * Representa uma Missão:
 *
 * ID: número inteiro ≥ 0 que identifica a missão;
 * Habilidades: ponteiro ao conjunto de habilidades necessárias para cumprir a missão;
 * Perigo: nível de perigo da missão;
 * Local: localização da missão (coordenada inteira X, Y ≥ 0).
 * Tentativa: número inteiro ≥ 0 mostra a quantidade de vezes que tentaram realizar a missão;
 * Cumprida: 0 ou 1 indica se a missão foi cumprida (1) ou não (0);
*/
struct missao_t {
    int id;
    struct cjto_t *habilidades;
    int perigo;
    struct coordenada_t local;
    int tentativa;
    int cumprida;
};

/*
 * Representa o Mundo da simulação:
 *
 * N_herois: número total de heróis no mundo;
 * Herois: vetor representando todos os heróis;
 * N_bases: número total de bases no mundo;
 * Bases: vetor representando todas as bases;
 * N_missoes: número total de missões a cumprir;
 * Missoes: vetor representando todas as missões;
 * N_Habilidades: número de habilidades distintas possíveis;
 * TamanhoMundo: coordenadas máximas do mundo (coordenada inteira X, Y ≥ 0).;
 * Relogio: número inteiro ≥ 0 indicando o tempo atual no mundo;
 * Mortes: quantidade de heróis mortos;
 * Lef: ponteiro para a Lista de eventos futuros (Fila de prioridade);
 * Missoes_cumpridas: quantidade de missões que foram cumpridas no mundo;
 * Ev_processados: quantidade de eventos que foram processados no mundo;
 * Max_tentativas: o maior número de vezes que os heróis tentaram realizar uma mesma missão;
 * Min_tentativas: o menor número de vezes que os heróis tentaram realizar uma mesma missão;
 * Tentativas: a soma de todas as tentativas de realizar as missões;
*/
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

/*
 * Essas funções inicializam as suas respectivas structs para a simulação,
 * populando os campos com dados aleatórios, cujos limites já foram predeterminados.
*/

int inicia_mundo (struct mundo_t *m);

int inicia_herois (struct heroi_t herois[]);

int inicia_bases (struct base_t bases[]);

int inicia_missoes (struct missao_t missoes[]);

/*
 * Essas funções destroem as structs utilizadas na simulação,
 * liberando o espaço de memória que foi alocado dinâmicamente.
*/

void destroi_herois (struct heroi_t herois[]);

void destroi_bases (struct base_t bases[]);

void destroi_missoes (struct missao_t missoes[]);

#endif
