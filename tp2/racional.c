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

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna um número aleatório entre min e max, inclusive.
 * "range" determina o espaço em que o número deve cair.
 * A linha a seguir gera o número e move ele para o intervalo correto. */ 
long aleat (long min, long max) {
  long range = max - min + 1;

  return ((rand() % range) + min);
}

/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b) {
  long resto;

  if ((a == 0) || (b == 0))
    return -1;

  resto = a % b;

  while (resto != 0) {
    a = b;
    b = resto;
    resto = a % b;
  }

  return b;
}

long mmc (long a, long b) {
  return (a * b) / mdc(a, b);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r) {
  if (!valido_r(r))
  return r;
  
  // Cuida do caso em que se deve migrar o sinal e de quando ambos são negativos
  if (r.den < 0) {
    r.num = r.num * -1;
    r.den = r.den * -1;
  }

  // Para mdc inválido, "fator_de_simplificacao" recebe 1, deixando o racional inalterado
  int fator_de_simplificacao = abs( (int) mdc(r.num, r.den));

  r.num = r.num / fator_de_simplificacao;
  r.den = r.den / fator_de_simplificacao;

  return r;
}

/* implemente as demais funções de racional.h aqui */

struct racional cria_r (long numerador, long denominador) {
  struct racional r;

  r.num = numerador;
  r.den = denominador;
  
  return r;
}

int valido_r (struct racional r) {
  if (r.den == 0)
    return 0;
  else
    return 1;
}

struct racional sorteia_r (long min, long max) {
  long r_num = aleat(min, max);
  long r_den = aleat(min, max);

  struct racional r = cria_r(r_num, r_den);

  return simplifica_r(r);
}

void imprime_r (struct racional r) {
  r = simplifica_r(r);

  if (!valido_r(r))
    printf("NaN");
  else if (r.num == 0 || r.den == 1)
    printf("%ld", r.num);
  else if (r.num == r.den)
    printf("1");
  else
    printf("%ld/%ld", r.num, r.den);
}

int compara_r (struct racional r1, struct racional r2) {
  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);
  
  if (!valido_r(r1) || !valido_r(r2))
    return -2;
  if (r1.num * r2.den < r2.num * r1.den)
    return -1;
  if (r1.den == r2.den && r1.num == r2.num)
    return 0;
  else
    return 1;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3) {  
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  r3->den = mmc(r1.den, r2.den);
  r3->num = (r1.num * (r3->den / r1.den)) + (r2.num * (r3->den / r2.den));

  *r3 = simplifica_r(*r3);

  return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  r3->den = mmc(r1.den, r2.den);
  r3->num = (r1.num * (r3->den / r1.den)) - (r2.num * (r3->den / r2.den));

  *r3 = simplifica_r(*r3);

  return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  r3->den = r1.den * r2.den;
  r3->num = r1.num * r2.num;

  *r3 = simplifica_r(*r3);

  return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3) {
  if (!valido_r(r1) || !valido_r(r2) || r3 == NULL)
    return 0;

  r3->den = r1.den * r2.num;
  r3->num = r1.num * r2.den;

  if (!valido_r(*r3))
    return 0;
  
  *r3 = simplifica_r(*r3);

  return 1;
}
