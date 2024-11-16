
#include <stdlib.h>
#include "utils.h"

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