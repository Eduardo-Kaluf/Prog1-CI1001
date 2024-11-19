#ifndef UTILS
#define UTILS

struct coordenada_t {
    int x;
    int y;
};

int aleat(int min, int max);

struct coordenada_t cria_coordenada(int x, int y);

double d_cartesiana(struct coordenada_t p1, struct coordenada_t p2);

#endif
