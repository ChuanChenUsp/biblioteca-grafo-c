#include<stdlib.h>
#include<assert.h>

#ifndef CORE_H
#define CORE_H

typedef struct Edge{
    unsigned int u, v, w;
} Edge;
typedef struct Graph{
    unsigned int n, m;
    unsigned int **adj;
    Edge *edges;
} Graph;

Graph *graph_create(unsigned int n); // cria um grafo com n vértices
void graph_destroy(Graph *g); // libera a memória do grafo
unsigned int graph_get_vertices(const Graph *g); // retorna o número de vértice

#endif
