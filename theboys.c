// programa principal do projeto "The Boys - 2024/2"
// Autor: Eduardo Kaluf, GRR 20241770

// seus #includes vão aqui
#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{
    // iniciar o mundo

    // executar o laço de simulação

    // destruir o mundo

    struct fila_t *f = fila_cria();
    fila_imprime(f);
    int *valor = malloc(sizeof(int));
    if (valor == NULL) {
        return 1;
    }

    queue(f, 10);
    fila_imprime(f);
    queue(f, 20);
    fila_imprime(f);
    queue(f, 30);
    fila_imprime(f);
    queue(f, 40);
    fila_imprime(f);
    queue(f, 50);
    fila_imprime(f);

    printf("%d\n", fila_tamanho(f));

    printf("%d\n", dequeue(f, valor));
    fila_imprime(f);
    printf("%d\n", dequeue(f, valor));   
    fila_imprime(f);
    printf("%d\n", dequeue(f, valor));   
    fila_imprime(f);
    printf("%d\n", dequeue(f, valor));   
    fila_imprime(f);
    printf("vaiza? %d\n", fila_vazia(f));
    printf("%d\n", dequeue(f, valor));   
    fila_imprime(f);

    printf("%d\n", fila_tamanho(f));

    printf("vaiza? %d\n", fila_vazia(f));


    free(valor);
    fila_destroi(f);

    return (0) ;
}

