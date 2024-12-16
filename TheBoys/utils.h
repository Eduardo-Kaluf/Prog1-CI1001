/* 
 * Trabalho: TheBoys
 * Arquivo header para as funções utilitárias do projeto
 * Feito em 08/12/2024 para a disciplina CI1001 - Programação 1
*/

#ifndef UTILS
#define UTILS

// Representa um ponto em R^2 (X, Y).
struct coordenada_t {
    int x;
    int y;
};

/*
 * Armazena uma base e sua distância a determinado ponto.
 * Utilizada para armazenar a distância entre o local das bases e das missões.
*/
struct dist_base {
    int id;
    int distancia;
};

// Retorna um número aleatório entre min e max (incluso).
int aleat (int min, int max);

// Cria e retorna uma coordenada com os valores X e Y.
struct coordenada_t cria_coordenada (int x, int y);

// Retorna a distância cartesiana entre duas coordenadas passadas.
double d_cartesiana (struct coordenada_t p1, struct coordenada_t p2);

/*
 * Ordena um vetor de structs "dist_base" com base no campo "distancia".
 * O algoritmo utilizado para a ordenação é o InsertionSort.
*/
void ordena_distancias (struct dist_base v[], int n);

#endif
