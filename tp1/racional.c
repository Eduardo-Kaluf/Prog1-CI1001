/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */

#include <stdio.h>
#include <stdlib.h>

#include "racional.h"
#include "utils.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador) {
  struct racional r;

  r.num = numerador;
  r.den = denominador;
  
  return r;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r) {
  if (r.den == 0)
    return 0;
  else
    return 1;
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */

// O intervalo deve considerar min e max inclusivos
struct racional sorteia_r (long min, long max) {
  long r_num = aleat(min, max);
  long r_den = aleat(min, max);

  struct racional r = cria_r(r_num, r_den);

  return simplifica_r(r);
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1";
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r) {
  r = simplifica_r(r);
  
  if (!valido_r(r))
    printf("INVALIDO");
  else if (r.num == 0)
    printf("0");
  else if (r.den == 1)
    printf("%ld", r.num);
  else if (r.num == r.den)
    printf("1");
  else
    printf("%ld/%ld", r.num, r.den);
}

/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r (struct racional r1, struct racional r2) {
  if (!valido_r(r1))
    return r1;
  if (!valido_r(r2))
    return r2;
  
  long r_den = mmc(r1.den, r2.den);
  long r_num = (r1.num * (r_den / r1.den)) + (r2.num * (r_den / r2.den));

  return cria_r(r_num, r_den);
}

/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2) {
  if (!valido_r(r1))
    return r1;
  if (!valido_r(r2))
    return r2;
  
  long r_den = mmc(r1.den, r2.den);
  long r_num = (r1.num * (r_den / r1.den)) - (r2.num * (r_den / r2.den));

  return cria_r(r_num, r_den);
}

/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r (struct racional r1, struct racional r2) {
  if (!valido_r(r1))
    return r1;
  if (!valido_r(r2))
    return r2;
   
  long r_num = r1.num * r2.num;
  long r_den = r1.den * r2.den;

  return cria_r(r_num, r_den);
}

/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
struct racional divide_r (struct racional r1, struct racional r2) {
  if (!valido_r(r1))
    return r1;
  if (!valido_r(r2))
    return r2;
  
  long r_num = r1.num * r2.den;
  long r_den = r1.den * r2.num;

  return cria_r(r_num, r_den);
}

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max) {
  /*
   * "range" determina o espaço em que o número deve cair.
   * A linha a seguir gera o número e move ele para o intervalo correto.
  */ 

  long range = max - min + 1;

  return ((rand() % range) + min);
}

/* Máximo Divisor Comum entre a e b      */
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

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
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

/* implemente as demais funções aqui */