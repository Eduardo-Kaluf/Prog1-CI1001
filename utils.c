
#include <stdlib.h>
#include "utils.h"
#include "eventos.h"
#include <math.h>

int aleat (int min, int max) {
    int range = max - min + 1;

    return ((rand() % range) + min);
}

struct coordenada_t cria_coordenada(int x, int y) {
    struct coordenada_t c;

    c.x = x;
    c.y = y;

    return c;
}

// TODO
// int d_cartesiana(struct coordenada_t p1, struct coordenada_t p2) {
//     return sqrt(pow(p2.x - p1.x) + (p2.y - p1.y))
// }