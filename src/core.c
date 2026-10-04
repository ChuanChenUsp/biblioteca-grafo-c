#include<stdlib.h>
#include<stdio.h>
#include "core.h"


Graph *graph_create(unsigned int n){
    Graph *g = malloc(sizeof *g);
    if(g == NULL){
        fprintf(stderr, "Memória insuficiente!");
        return NULL;
    }

    g->n = n;
    g->m = 0;
    
    g->adj = malloc(n * sizeof *(g->adj));
    if(g->adj == NULL){
        fprintf(stderr, "Memória insuficiente!");
        return NULL;
    }
    
    for(int i = 0; i < n; i++){
        g->adj[i] = calloc(n, sizeof *(g->adj[i]));
        if(g->adj[i] == NULL){
            for(int prev = 0; prev < i; prev++){
                free(g->adj[prev]); //previnir memomry leak das alocações prévias sucedidas.
            }
            free(g->adj);
            free(g);

            fprintf(stderr, "Memória insuficiente!");
            return NULL;
        }
    }
    return g;
}
void graph_destroy(Graph *g){
    if(g == NULL) return;

    for(int i = 0; i < g->n; i++) free(g->adj[i]);
    free(g->adj);
    free(g);
}
unsigned int graph_get_vertices(const Graph *g){
    if(g == NULL) return 0;
    return g->n;
}



