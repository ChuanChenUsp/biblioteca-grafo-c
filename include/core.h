#include<stdlib.h>
#include<assert.h>

#ifndef CORE_H
#define CORE_H

struct Edge{
    unsigned int u, v, w;
};

struct Graph{
    unsigned int n;
    unsigned int **adj;
    Edge *edges;
};

Graph *graph_create(size_t n);
void graph_destroy(Graph *g);
size_t graph_get_vertices(const Graph *g);
Edge *graph_get_edges(const Graph *g, size_t *count);

#endif
