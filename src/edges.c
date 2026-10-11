#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "edges.h"

bool graph_add_edge(Graph *g, unsigned int u, unsigned int v, unsigned int w){
    if(g == NULL){
        fprintf(stderr, "Grafo não inicializado!");
        return false;
    }
    if(u < g->n && v < g->n){
        g->adj[u][v] = g->adj[v][u] = w;
        return true;
    }
    return false;
}
bool graph_remove_edge(Graph *g,unsigned int u,unsigned int v){
    return graph_add_edge(g, u, v, 0);
}
int graph_get_weight(const Graph *g,unsigned int u,unsigned int v){
    if(g == NULL){
        fprintf(stderr, "Grafo não inicializado!");
        return 0;
    }
    if(u < g->n && v < g->n) return g->adj[u][v];
    if(u >= g->n) fprintf(stderr, "%d não é vértice deste grafo!", u);
    if(v >= g->n) fprintf(stderr, "%d não é vértice deste grafo!", v);
    return 0; 
}

Edge new_edge(unsigned int u, unsigned int v, unsigned int w){
    Edge e;
    e.u = u;
    e.v = v;
    e.w = w;
    return e;
}

Edge *graph_get_edges(const Graph *g, int *count){
    if(g == NULL){
        fprintf(stderr, "Grafo não inicializado!");
        return NULL;
    }
    if (count == NULL) return NULL;

    *count = 0;
    for(int i = 0; i < g->n; i++){
        for(int j = i; j < g->n; j++){
            if(g->adj[i][j] != 0){
                (*count)++;
            }
        }
    }
    Edge *e = malloc(*count * sizeof *e);
    if(e == NULL){
        if (*count != 0)
            fprintf(stderr, "Memória insuficiente!");
        return NULL;
    }

    *count = 0;
    for(int i = 0; i < g->n; i++){
        for(int j = i; j < g->n; j++){
            if(g->adj[i][j] != 0){
                e[(*count)++] = new_edge(i, j, g->adj[i][j]);
            }
        }
    }

    return e;
}
int graph_degree(const Graph *g, unsigned int u){
    if(g == NULL){
        fprintf(stderr, "Grafo não inicializado!");
        return NULL;
    }
    if(u >= g->n){
        fprintf(stderr, "%d não é vértice deste grafo!", u);
        return NULL;
    } 
    int deg = (int)(g->adj[u][u] != 0);
    for(int i = 0; i < g->n; i++){
        if(g->adj[u][i] != 0) deg++;
    }
    return deg;
}
