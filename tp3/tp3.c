/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>

#include "racional.h"
#include "utils.h"

int main () {
  int n;
  struct racional somatorio;
  struct racional **v;

  scanf("%d", &n);

  if (n >= 100 || n <= 0)
    return -1;

  v = cria_vetor(n);

  if (v == NULL) {
    return -1;
  }

  le_vetor(v, n);

  imprime_vetor(v, n);

  elimina_invalidos(v, &n);

  imprime_vetor(v, n);

  ordena_vetor(v, n);

  imprime_vetor(v, n);

  soma_vetor(v, &somatorio, n);

  imprime_soma(&somatorio);

  libera_vetor(v, n);

  imprime_vetor(v, n);

  free(v);

  return (0) ;
}

