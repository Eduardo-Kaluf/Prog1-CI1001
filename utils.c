
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

double d_cartesiana(struct coordenada_t p1, struct coordenada_t p2) {
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

void ordena_dist_bases(struct dist_base v[], int n) {
    int k = 1;

    do {
        k = k * 3 + 1;
    } while (k <= n);

    do {
        k = k / 3;

        shell_sort(v, k, n);
        
    } while (k != 1);
}

void shell_sort(struct dist_base v[], int k, int n) {
    int i, j;
    struct dist_base aux;

    for (i = k + 1; i <= n; i++) {
        aux = v[i];
        j = i;

        while (j > k && v[j - k].distancia > aux.distancia ) {

            v[j] = v[j - k];

            j = j - k;
            if (j <= k)
                break;
        }

        v[j] = aux;
    }
}
