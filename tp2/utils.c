/* 
 * Tipos Abstratos de Dados - TADs
 *
 * Arquivo de implementação para funções utilitárias
 * Essas funções trabalham com vetores que possuem o TAD "racional"
 * 
*/

#include <stdio.h>

#include "utils.h"

void le_vetor (struct racional v[], int n) {
  for (int i = 0; i < n; i++) {
    int num, den;
    scanf("%d %d", &num, &den);

    v[i] = cria_r(num, den);
  }
}

void imprime_vetor (struct racional v[], int n) {
  printf("VETOR = ");
  
  for (int i = 0; i < n; i++) {
    imprime_r(v[i]);
    printf(" ");
  }

  printf("\n");
}

void elimina_invalidos (struct racional v[], int *n) {
  int novo_tam = *n;
  
  // Percorre o vetor inteiro de trás para frente
  for (int i = *n - 1; i > -1; i--) {
    if (!valido_r(v[i])) {
      // Move a parte já percorrida do vetor para a esquerda 
      for (int j = i; j < *n - 1; j++) {
        v[j] = v[j + 1];
      }

      novo_tam = novo_tam - 1;
    }
  }

  *n = novo_tam;
}

void soma_vetor (struct racional v[], struct racional *somatorio, int n) {
  somatorio->num = 0;
  somatorio->den = 1;

  for (int i = 0; i < n; i++) {
    soma_r(*somatorio, v[i], somatorio);
  }
}

void ordena_vetor (struct racional v[], int n) {
  for (int passo = 0; passo < n - 1; passo++) {

    for (int i = 0; i < n - passo - 1; i++) {
      if (compara_r(v[i], v[i + 1]) == 1) {
        struct racional aux = v[i];

        v[i] = v[i + 1];
        v[i + 1] = aux;

      }
    }
  }
}
