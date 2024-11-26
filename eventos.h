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
 * Atualiza as informações que se relacionam as missões.
 * Que serão utilizadas para gerar o relatório no final do mundo.
*/
void att_ev_mi_info (struct mundo_t *m, int mi_id, int b_id, int bmp);

/*
 * Cria e adiciona um evento genérico na LEF.
*/
int add_evento (struct mundo_t *m, int tipo, int tempo, int info1, int info2);

/*
 * Representa um herói chegando em uma Base.
 *  - Ao chegar, o herói analisa o tamanho da Fila e as vagas da Base 
 *  - Então decide se ESPERA para entrar ou DESISTE
*/
void chega (struct ev_hb *e, struct mundo_t *m);

/*
 * O herói entra na Fila de espera da Base.
 *  - Assim que o herói entra na Fila, AVISA o porteiro da Base
*/
void espera (struct ev_hb *e, struct mundo_t *m);

/*
 * O herói desiste de entrar na Base.
 *  - Escolhe uma Base aleatória e VIAJA para lá. 
*/
void desiste (struct ev_hb *e, struct mundo_t *m);

/*
 * A Fila de espera de certa Base é tratada.
 *  - Enquanto houver vagas na Base:
 *    - O Herói ENTRA na Base
 *    - Retira o primeiro Herói da Fila
 *    - Adiciona-o no conjunto de heróis presentes da Base
*/
void avisa (struct ev_b *e, struct mundo_t *m);

/*
 * O Herói entra na Base.
 *  - É calculado o tempo de permanência na Base (TPB)
 *  - O Herói agenda quando ele SAI da Base
*/
void entra (struct ev_hb *e, struct mundo_t *m);

/*
 * O Herói sai da Base.
 *  - O Herói é retirado do cojunto de Heróis presentes da Base
 *  - Escolhe uma Base aleatória e VIAJA para lá.
 *  - Assim que o Herói sai da Base ele AVISA o porteiro
*/
void sai (struct ev_hb *e, struct mundo_t *m);

/*
 *  O Herói se desloca para uma Base.
 *   - É calculado a duração da viagem
 *   - Agenda a quando o Herói CHEGA na Base
*/
void viaja (struct ev_hb *e, struct mundo_t *m);

/*
 * O Herói morre.
 *  - Retira-o do conjunto de Heróis presentes da Base
 *  - Muda seu status para morto
 *  - Assim que o Herói morre, alguém AVISA o porteiro
*/
void morre (struct ev_hm *e, struct mundo_t *m);

/*
 * Uma missão é disparada.
 *   - Encontra a Base mais próxima (BMP) capaz de realizar a missão
 *   - A BMP é apta a realizar a missão se a união das habilidades dos Heróis presentes nela
 *     Abrange as habilidades exigidas da missão 
 *   - Caso seja possível realizar a missão:
 *     - A missão é cumprida
 *     - Verifica quem MORRE na missão
 *     - Aumenta a experiência dos Herois que sobreviveram
 *   - Caso não seja possível realiar a missão:
 *     - Marca a MISSÃO como ímpossivel e agenda ela para o dia seguinte
*/
void missao (struct ev_m *e, struct mundo_t *m);

/*
 * Encerra a simulação
 *  - Apresenta as estatísticas dos Heróis, Bases e Missões
*/
void fim (struct mundo_t *m);

/*
 * Função responsável por loopar os eventos.
 *  - Retira o próximo evento da LEF
 *  - Verifica se o evento é válido
 *  - Chama a função responsável por tratar aquele evento em específico
*/
void simular_eventos (struct mundo_t *m);

#endif
