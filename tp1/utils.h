/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de header auxiliar para TAD racional.
 * Feito em 16/09/2024 para a trabalho 1 da disciplina CI1001 - Programação 1.
 *
 * Este arquivo contém o protótipo de funções auxiliares.
 * Serão utilizadas ao implementar racional.h
 *
*/

#ifndef UTILS
#define UTILS

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max);

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b);

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b);

/* Recebe um número racional e o simpfica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r);

#endif
