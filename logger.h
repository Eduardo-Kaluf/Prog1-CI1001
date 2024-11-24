/* 
 * Trabalho: TheBoys
 * Arquivo header para as funções de log
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#ifndef LOGGER
#define LOGGER

#include "theboys.h"

void log_chega (int tempo, int h_id, struct base_t b);

void log_espera (int tempo, int h_id, struct base_t b);

void log_desiste (int tempo, int h_id, int b_id);

void log_avisa_fila (int tempo, struct base_t b);

void log_avisa_admite (int tempo, int b_id, int h_id);

void log_entra (int tempo, int h_id, struct base_t b, int saida);

void log_sai (int tempo, int h_id, struct base_t b);

void log_viaja (int tempo, struct heroi_t h, int b_id, int distancia, int chegada);

void log_morre (int tempo, int h_id, int mi_id);

void log_missao_tentativa (int tempo, struct missao_t mi);

void log_missao_cumprida (int tempo, int b_id, int mi_id, struct cjto_t *uni);

void log_missao_impossivel (int tempo, int mi_id);

void log_fim_morto (int h_id);

void log_fim_vivo (int h_id);

void log_heroi_info (struct heroi_t h);

void log_fim_base (struct base_t b);

void log_statisticas(struct mundo_t *m);

#endif
