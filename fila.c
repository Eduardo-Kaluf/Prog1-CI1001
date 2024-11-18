// TAD fila implementação
// Autor: Eduardo Kaluf, GRR 20241770

#include "fila.h"

#include <stdlib.h>
#include <stdio.h>

struct fila_t *fila_cria () {
    struct fila_t *f;

    if (!(f = malloc(sizeof(struct fila_t))))
        return NULL;

    f->prim = NULL;
    f->ult = NULL;
    f->tamanho = 0;

    return f;
}

struct fila_t *fila_destroi (struct fila_t *f) {
    struct nodo_t *p; 

    // fila nula
    if (f == NULL)
        return NULL;

    while (f->prim != NULL) {
        p = f->prim;
        f->prim = f->prim->prox;
        free(p);
        (f->tamanho)--;
    }

    free(f);

    return NULL;
}

int enqueue (struct fila_t *f, int valor) {
    struct nodo_t *novo;

    // Trata casos inválidos
    if (f == NULL || !(novo = malloc(sizeof(struct nodo_t))))
        return -1;

    novo->valor = valor;

    if (f->tamanho == 0)
        f->prim = novo;
    else 
        f->ult->prox = novo;
    
    novo->prox = NULL;
    f->ult = novo;

    return ++(f->tamanho);
}

int dequeue (struct fila_t *f, int *valor) {
    struct nodo_t *aux;

    // Trata casos inválidos
    if (f == NULL || valor == NULL || f->tamanho == 0)
        return -1;

    *valor = f->prim->valor;
    aux = f->prim;
    f->prim = aux->prox;
    free(aux);

    if (f->prim == NULL)
        f->ult = NULL;

    return --(f->tamanho);
}

int fila_tamanho (struct fila_t *f) {
    if (f == NULL)
        return -1;

    return f->tamanho;
}

int fila_vazia (struct fila_t *f) {
    if (f == NULL)
        return -1;

    if (f->tamanho == 0)
        return 1;
    
    return 0;
}

void fila_imprime (struct fila_t *f) {
    struct nodo_t *p;

    // Trata casos inválidos
    if (f == NULL || f->tamanho == 0)
        return;

    p = f->prim;

    printf("[ ");

    for (int i = 0; i < f->tamanho - 1; i++) {

        printf("%d, ", p->valor);
        p = p->prox;
    }

    printf("%d ]\n", p->valor);
    
    return;
}