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

void ordena_dist_bases(struct dist_base v[], int n);

void shell_sort(struct dist_base v[], int k, int n);

#endif
