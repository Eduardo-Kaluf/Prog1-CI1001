/* 
 * Trabalho: TheBoys
 * Arquivo de implementação para as funções utilitárias do projeto
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "eventos.h"

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

// Ordena um vetor de "struct dist_base" utilizando o InsertionSort
void ordena_distancias(struct dist_base v[], int n) {
    for (int i = 1; i < n; ++i) {
        struct dist_base key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j].distancia > key.distancia) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
    }
}
