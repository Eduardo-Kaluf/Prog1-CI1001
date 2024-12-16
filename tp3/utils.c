/* 
 * Tipos Abstratos de Dados - TADs
 *
 * Arquivo de implementação para funções utilitárias
 * Essas funções trabalham com vetores que possuem o TAD "racional"
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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

int simplifica_r (struct racional *r) {
  if (!valido_r(r) || r == NULL)
    return 0;
  
  // Cuida do caso em que se deve migrar o sinal e de quando ambos são negativos
  if (r->den < 0) {
    r->num = r->num * -1;
    r->den = r->den * -1;
  }

  // Para mdc inválido, "fator_de_simplificacao" recebe 1, deixando o racional inalterado
  int fator_de_simplificacao = labs(mdc(r->num, r->den));

  r->num = r->num / fator_de_simplificacao;
  r->den = r->den / fator_de_simplificacao;

  return 1;
}

struct racional **cria_vetor (int n) {
  struct racional **v;

  v = malloc(sizeof(struct racional*) * n);
  if (v == NULL)
    return NULL;

  return v;
}

void le_vetor (struct racional *v[], int n) {
  for (int i = 0; i < n; i++) {
    int num, den;
    scanf("%d %d", &num, &den);

    v[i] = cria_r(num, den);
  }
}

void imprime_vetor (struct racional *v[], int n) {
  printf("VETOR = ");
  
  for (int i = 0; i < n; i++) {
    imprime_r(v[i]);
    printf(" ");
  }

  printf("\n");
}

void elimina_invalidos (struct racional *v[], int *n) {
  int novo_tam = *n;
  
  // Percorre o vetor inteiro de trás para frente
  for (int i = *n - 1; i > -1; i--) {
    if (!valido_r(v[i])) {
      // Libera o espaço do elemento inválido
      destroi_r(v[i]);
      v[i] = NULL;

      // Move a parte já percorrida do vetor para a esquerda 
      for (int j = i; j < *n - 1; j++) {
        v[j] = v[j + 1];
      }

      novo_tam = novo_tam - 1;
    }
  }

  *n = novo_tam;
}

void soma_vetor (struct racional *v[], struct racional *somatorio, int n) {
  somatorio->num = 0;
  somatorio->den = 1;

  for (int i = 0; i < n; i++) {
    soma_r(somatorio, v[i], somatorio);
  }
}

void ordena_vetor (struct racional *v[], int n) {
  for (int passo = 0; passo < n - 1; passo++) {

    for (int i = 0; i < n - passo - 1; i++) {
      if (compara_r(v[i], v[i + 1]) == 1) {
        struct racional *aux = v[i];

        v[i] = v[i + 1];
        v[i + 1] = aux;

      }
    }
  }
}

void libera_vetor (struct racional *v[], int n) {
  for (int i = 0; i < n; i++) {
    destroi_r(v[i]);
    v[i] = NULL;
  }
}

void imprime_soma (struct racional *somatorio) {
  printf("SOMA = ");

  imprime_r(somatorio);
  
  printf("\n");
}

