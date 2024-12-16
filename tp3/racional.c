/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

#include <stdio.h>
#include <stdlib.h>

#include "racional.h"
#include "utils.h"

struct racional *cria_r (long numerador, long denominador) {
  struct racional *r;

  if (!(r = malloc (sizeof(struct racional)))) {
    return NULL;
  }

  r->num = numerador;
  r->den = denominador;

  return r;
}

void destroi_r (struct racional *r) {
  free(r);
}

/* A comparação r == NULL deve ficar na esquerda
 * Assim se evita que r->den acesse um local inválido da memória */ 
int valido_r (struct racional *r) {
  if (r == NULL || r->den == 0)
    return 0;

  return 1;
}

void imprime_r (struct racional *r) {
  if (r == NULL) {
    printf("NULL");
    return;
  }

  simplifica_r(r);

  if (!valido_r(r)) {
    printf("NaN");
    return;
  }

  if (r->num == 0 || r->den == 1) {
    printf("%ld", r->num);
    return;
  }

  if (r->num == r->den) {
    printf("1");
    return;
  }
  
  printf("%ld/%ld", r->num, r->den); 

  return;
}

int compara_r (struct racional *r1, struct racional *r2) {
  if (!valido_r(r1) || !valido_r(r2))
    return -2;

  int r_mmc = mmc(r1->den, r2->den);

  if ((r1->num * (r_mmc / r1->den)) < (r2->num * (r_mmc / r2->den)))
    return -1;
  if (r1->den == r2->den && r1->num == r2->num)
    return 0;
  else
    return 1;
}

/* Operações
 * As variaveis "r3_den" e "r3_num" são utilizadas para evitar conflito nas contas
 * Ao alterar o valor diretamente em r3, poderiamos estar alterando tambem r1 ou r2 dependendo de como a função foi chamada */
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (r3 == NULL || !valido_r(r1) || !valido_r(r2))
    return 0;

  long r3_den = mmc(r1->den, r2->den);
  long r3_num = (r1->num * (r3_den / r1->den)) + (r2->num * (r3_den / r2->den));

  r3->den = r3_den;
  r3->num = r3_num;

  simplifica_r(r3);

  return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (r3 == NULL || !valido_r(r1) || !valido_r(r2))
    return 0;

  long r3_den = mmc(r1->den, r2->den);
  long r3_num = (r1->num * (r3_den / r1->den)) - (r2->num * (r3_den / r2->den));

  r3->den = r3_den;
  r3->num = r3_num;

  simplifica_r(r3);

  return 1;
}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (r3 == NULL || !valido_r(r1) || !valido_r(r2))
    return 0;

  long r3_den = r1->den * r2->den;
  long r3_num = r1->num * r2->num;

  r3->den = r3_den;
  r3->num = r3_num;

  simplifica_r(r3);

  return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  if (r3 == NULL || !valido_r(r1) || !valido_r(r2))
    return 0;

  long r3_den = r1->den * r2->num;
  long r3_num = r1->num * r2->den;

  r3->den = r3_den;
  r3->num = r3_num;

  if (!valido_r(r3))
    return 0;
  
  simplifica_r(r3);

  return 1;
}

