
#ifndef CORE_H
#define CORE_H
#include<stdlib.h>
typedef struct Edge{
    unsigned int u, v, w;
} Edge;
typedef struct Graph{
    unsigned int n, m;
    unsigned int **adj;
} Graph;

/**
 * @brief Criar um grafo com @p n vértices
 *
 * @param n        Número de vértices.
 * @return Ponteiro para grafo criado, ou NULL no caso de erro. 
 */
Graph *graph_create(unsigned int n);

/**
 * @brief Liberar a memória de um grafo e destruí-lo.
 *
 * @param g        Ponteiro para o grafo a ser destruido.
 */
void graph_destroy(Graph *g);

#endif
