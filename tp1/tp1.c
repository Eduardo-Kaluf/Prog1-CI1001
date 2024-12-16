/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */

#include <stdio.h>
#include <stdlib.h>

#include "racional.h"

/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */

    int n, max;

    scanf("%d %d", &n, &max);

    if (n <= 0 || n >= 100)
        return 1;

    if (max <= 0 || max >= 30)
        return 1;

    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);
        
        struct racional r1 = sorteia_r(max * -1, max);
        struct racional r2 = sorteia_r(max * -1, max);

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        printf(" ");

        if (!valido_r(r1) || !valido_r(r2)) {
            printf("NUMERO INVALIDO");
            return 1;
        }

        struct racional soma          = soma_r(r1, r2);
        struct racional subtracao     = subtrai_r(r1, r2);
        struct racional multiplicacao = multiplica_r(r1, r2);
        struct racional divisao       = divide_r(r1, r2);
        
        if (!valido_r(divisao)) {
            printf("DIVISAO INVALIDA");
            return 1;
        }

        imprime_r(soma);
        printf(" ");
        imprime_r(subtracao);
        printf(" ");
        imprime_r(multiplicacao);
        printf(" ");
        imprime_r(divisao);

        printf("\n");

    }

    return (0);
}
