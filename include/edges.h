
#ifndef EDGES_H
#include<stdlib.h>
#include<stdbool.h> 
#include "core.h"
#define EDGES_H

bool graph_add_edge(Graph *g, unsigned int u, unsigned int v, unsigned int w); // adiciona a aresta u-v com peso w
bool graph_remove_edge(Graph *g, unsigned int u,unsigned int v); // remove a aresta entre u e v 
int graph_get_weight(const Graph *g, unsigned int u, unsigned int v); // retorna peso da aresta u-v, retorna 0 se não existe aresta u-v.
Edge *graph_get_edges(const Graph *g, int *count); // retorna as arestas e sua quantidade
int graph_degree(const Graph *g, unsigned int u); // retorna o grau do vértice u
    
#endif                         
