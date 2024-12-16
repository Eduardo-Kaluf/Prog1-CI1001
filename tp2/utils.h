/* 
 * Tipos Abstratos de Dados - TADs
 *
 * Este arquivo contém o protótipo de funções auxiliares
 * para manipular vetores de números racionais.
 * 
*/

#ifndef UTILS
#define UTILS

#include "racional.h"

/* Le um vetor de racionais.
 * Deve receber numerador e denominador, nesta ordem. */
void le_vetor (struct racional v[], int n);

/* Imprime um vetor de racionais.
 * Imprime a mensagem "VETOR = "
 * Após isso, imprime todos os números racionais do vetor, separados por um único espaço 
 * Por fim, imprime uma linha em branco. */
void imprime_vetor (struct racional v[], int n);

/* Elimina números racionais inválidos de um vetor.
 * Percorre o vetor de racionais de trás para frente, verificando se o número é valido ou não
 * Em casos positivos:
   - Remove o racional inválido; 
   - Move o vetor já analisado 1 posição para a esquerda; 
   - Por fim diminui o tamanho do vetor em 1. */
void elimina_invalidos (struct racional v[], int *n);

/* Calcula a soma de todos os racionais de um vetor e a retorna no parametro *somatorio.
 * Define somatório como o elemento neutro da soma
 * Percorre o vetor de racionais somando-os um por um. */
void soma_vetor (struct racional v[], struct racional *somatorio, int n);

/* Ordena um vetor de racionais.
 * Percorre o vetor de racionais e o ordena 
 * A função utiliza o algoritmo "Bubble Sort". */
void ordena_vetor (struct racional v[], int n);

#endif
