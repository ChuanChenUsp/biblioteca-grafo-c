#include <stdlib.h>
#include <stdio.h>
#include "traversal.h"


static bool dfs_reach(const Graph *g, unsigned int atual, unsigned int destino, bool *visitado){
    if (atual == destino) return true;
    visitado[atual] = true;
    for (unsigned int i = 0; i < g->n; i++){
        if (g->adj[atual][i] != 0 && !visitado[i])
            if(dfs_reach(g, i, destino, visitado)) return true;

    }
    return false;
}

bool graph_is_reachable(const Graph *g, unsigned int u,unsigned int v){
    if (g == NULL || (u < 0 || u >= g->n) || (v < 0 || v >= g->n)) return false;
    bool *visited = calloc(g->n, sizeof *visited);
    if (visited == NULL) {
        free(visited);
        fprintf(stderr, "Memória insuficiente!\n");
        return false;
    }
    bool answer = dfs_reach(g, u, v, visited);
    free(visited);
    return answer;
}
