/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>

#include "racional.h"
#include "utils.h"

#define TAM 100

int main ()
{
  struct racional v[TAM];
  int n;

  scanf("%d", &n);

  if (n >= 100 || n <= 0)
    return -1; 

  le_vetor(v, n);

  imprime_vetor(v, n);

  elimina_invalidos(v, &n);

  imprime_vetor(v, n);

  ordena_vetor(v, n);

  imprime_vetor(v, n);

  struct racional somatorio;
  soma_vetor(v, &somatorio, n);
  
  printf("SOMA = ");
  imprime_r(somatorio);

  printf("\n");

  return (0) ;
}
