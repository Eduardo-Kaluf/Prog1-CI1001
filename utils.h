/* 
 * Trabalho: TheBoys
 * Arquivo header para as funções utilitárias do projeto
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#ifndef UTILS
#define UTILS

struct coordenada_t {
    int x;
    int y;
};

struct dist_base {
    int id;
    int distancia;
};

int aleat(int min, int max);

struct coordenada_t cria_coordenada(int x, int y);

double d_cartesiana(struct coordenada_t p1, struct coordenada_t p2);

void ordena_distancias(struct dist_base v[], int n);

#endif
