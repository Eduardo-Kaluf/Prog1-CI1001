/* 
 * Trabalho: TheBoys
 * Arquivo de implementação para o TAD lista
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

struct lista_t *lista_cria () {
    struct lista_t *l;

    if (!(l = malloc(sizeof(struct lista_t))))
        return NULL;

    l->prim = NULL;
    l->ult = NULL;
    l->tamanho = 0;

    return l;
}

struct lista_t *lista_destroi (struct lista_t *lst) {
    struct item_t *p; 

    // Lista nula
    if (lst == NULL)
        return NULL;

    while (lst->prim != NULL) {
        p = lst->prim;
        lst->prim = lst->prim->prox;
        free(p);
        (lst->tamanho)--;
    }

    free(lst);

    return NULL;
}

/*
 * Insere o elemento quando a lista está vazia
 * Utilizada em "lista_insere" como uma função auxiliar. 
*/
int lista_insere_vazia(struct lista_t *lst, struct item_t *novo) {
    lst->prim = novo;
    lst->ult = novo;

    return (lst->tamanho)++;
}

int lista_insere (struct lista_t *lst, int item, int pos) {
    struct item_t *p; 
    struct item_t *novo;

    // Trata casos inválidos
    if (lst == NULL || pos < -1 || !(novo = malloc(sizeof(struct item_t))))
        return -1;

    novo->valor = item;

    // Insere no início
    if (pos == 0) {
        novo->ant = NULL;

        // Lista vazia
        if (lst->tamanho == 0) {
            novo->prox = NULL;

            return lista_insere_vazia(lst, novo);
        }

        novo->prox = lst->prim;
        lst->prim->ant = novo;
        lst->prim = novo;

        return (lst->tamanho)++;
    }

    // Insere no fim
    if (pos >= lst->tamanho || pos == -1) {
        novo->prox = NULL;

        // Lista vazia
        if (lst->tamanho == 0) {
            novo->ant = NULL;

            return lista_insere_vazia(lst, novo);
        }
        
        novo->ant = lst->ult;
        lst->ult->prox = novo;
        lst->ult = novo;
        
        return (lst->tamanho)++;
    }

    p = lst->prim;

    // Caso genérico
    for (int i = 0; i < pos; i++) {
        p = p->prox;
    }
    
    novo->ant = p->ant;
    p->ant->prox = novo;
    p->ant = novo;
    novo->prox = p;

    return (lst->tamanho)++;
}

int lista_retira (struct lista_t *lst, int *item, int pos) {
    struct item_t *p; 
    struct item_t *aux;

    // Trata casos inválidos
    if (lst == NULL || item == NULL || pos >= lst->tamanho || pos < -1 || lst->tamanho == 0)
        return -1;
    
    p = lst->prim;
    *item = p->valor;

    // Se existe apenas um elemento na lista, retira ele
    if (lst->tamanho == 1) {
        lst->prim = NULL;
        lst->ult = NULL;
        free(p);

        return (lst->tamanho)--;
    }

    // Retira do início
    if (pos == 0) {
        lst->prim = lst->prim->prox;
        lst->prim->ant = NULL;
        free(p);

        return (lst->tamanho)--;
    }

    // Retira do fim
    if (pos == -1 || pos == lst->tamanho - 1) {
        aux = lst->ult;
        *item = aux->valor;
        aux->ant->prox = NULL;
        lst->ult = aux->ant;
        free(aux);

        return (lst->tamanho)--;
    }

    // Caso genérico
    for (int i = 0; i < pos; i++) {
        p = p->prox;
    }

    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    free(p);

    return (lst->tamanho)--;
}

int lista_consulta (struct lista_t *lst, int *item, int pos) {
    struct item_t *p;

    // Trata casos inválidos
    if (lst == NULL || item == NULL || pos >= lst->tamanho || pos < -1 || lst->tamanho == 0)
        return -1;

    p = lst->prim;

    // Consulta do início
    if (pos == 0) {
        *item = lst->prim->valor;

        return lst->tamanho;
    }

    // Consulta do final
    if (pos == -1 || pos == lst->tamanho - 1) {
        *item = lst->ult->valor;
        
        return lst->tamanho; 
    }

    // Caso genérico
    for (int i = 0; i < pos; i++) {
        p = p->prox;
    }

    *item = p->valor;

    return lst->tamanho; 
}

int lista_procura (struct lista_t *lst, int valor) {
    struct item_t *p;

    // Trata casos inválidos
    if (lst == NULL || lst->tamanho == 0)
        return -1;

    p = lst->prim;
    
    // Caso genérico
    for (int i = 0; i < lst->tamanho; i++) {
        if (p->valor == valor)
            return i;

        p = p->prox;
    }

    return -1;
}

int lista_tamanho (struct lista_t *lst) {
    if (lst == NULL)
        return -1;

    return lst->tamanho;
}

void lista_imprime (struct lista_t *lst) {
    struct item_t *p;

    // Trata casos inválidos
    if (lst == NULL || lst->tamanho == 0)
        return;

    p = lst->prim;

    for (int i = 0; i < lst->tamanho - 1; i++) {
        printf("%d ", p->valor);
        p = p->prox;
    }

    printf("%d", p->valor);
    
    return;
}
