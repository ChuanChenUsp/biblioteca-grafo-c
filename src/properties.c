#include <stdlib.h>
#include <stdbool.h> 
#include <stdio.h>
#include "properties.h"

// Visita todos os vértices alcançáveis.
static void dfs(const Graph *g, unsigned int start, bool *visited, unsigned int *stack) {
    unsigned int top = 0;

    stack[top++] = start;
    visited[start] = true;

    while (top > 0) {
        unsigned int u = stack[--top];

        for (unsigned int v = 0; v < g->n; v++) {
            if (g->adj[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                stack[top++] = v;
            }
        }
    }
}

// DFS para detectar ciclos em grafos não direcionados.
static bool dfs_has_cycle(const Graph *g, unsigned int start, bool *visited, unsigned int *stack, int *parents) {
    unsigned int top = 0;

    stack[top++] = start;
    visited[start] = true;

    while (top > 0) {
        unsigned int u = stack[--top];

        for (unsigned int v = 0; v < g->n; v++) {
            if (g->adj[u][v] == 0)
                continue;

            // Um laço representa um ciclo.
            if (u == v)
                return true;

            if (!visited[v]) {
                visited[v] = true;
                parents[v] = (int)u;
                stack[top++] = v;
            }
            else if (parents[u] != (int)v) {
                return true;
            }
        }
    }

    return false;
}

// Verifica se todos os vértices do grafo são alcançáveis.
bool graph_is_connected(const Graph *g) {
    // Verifica se o grafo foi inicializado.
    if (g == NULL) {
        fprintf(stderr, "Grafo não inicializado!");
        return false;
    }

    // Um grafo vazio é considerado conexo.
    if (g->n == 0)
        return true;

    // Aloca e inicializa o vetor de vértices visitados.
    bool *visited = calloc(g->n, sizeof *visited);
    unsigned int *stack = malloc(g->n * sizeof *stack);

    if (stack == NULL || visited == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        free(visited);
        free(stack);
        return false;
    }

    dfs(g, 0, visited, stack);

    bool connected = true;

    for (unsigned int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            connected = false;
            break;
        }
    }

    free(visited);
    free(stack);

    return connected;
}

// Verifica se o grafo possui algum ciclo.
bool graph_has_cycle(const Graph *g) {
    // Verifica se o grafo foi inicializado.
    if (g == NULL) {
        fprintf(stderr, "Grafo não inicializado!");
        return false;
    }

    // Um grafo vazio não possui ciclos.
    if (g->n == 0)
        return false;

    // Aloca o vetor de vértices visitados.
    bool *visited = calloc(g->n, sizeof *visited);

    // Aloca a pilha utilizada na busca em profundidade.
    unsigned int *stack = malloc(g->n * sizeof *stack);
   
    // Armazena o vértice predecessor de cada vértice.
    int *parents = malloc(g->n * sizeof *parents);
  
    if (visited == NULL || stack == NULL || parents == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        free(visited);
        free(stack);
        free(parents);
        return false;
    }

    // Inicializa todos os predecessores como inexistentes.
    for (unsigned int i = 0; i < g->n; i++)
        parents[i] = -1;

    bool cycle = false;
    
    // Percorre todas as componentes do grafo.
    for (unsigned int i = 0; i < g->n; i++) {
        if (!visited[i] && dfs_has_cycle(g, i, visited, stack, parents)) {
            cycle = true;
            break;
        }
    }

    free(visited);
    free(stack);
    free(parents);

    return cycle;
}

// Um grafo é uma árvore se for conexo e não possuir ciclos.
bool graph_is_tree(const Graph *g) {
    return graph_is_connected(g) && !graph_has_cycle(g);
}

// Verifica se o grafo é uma floresta (não possui ciclos).
bool graph_is_forest(const Graph *g) {
    if (g == NULL) {
        fprintf(stderr, "Grafo não inicializado!");
        return false;
    }

    return !graph_has_cycle(g);
}

// Verifica se o grafo é bipartido.
bool graph_is_bipartite(const Graph *g) {
    if (g == NULL) {
        fprintf(stderr, "Grafo não inicializado!");
        return false;
    }

    if (g->n == 0)
        return true;

    int *colors = malloc(g->n * sizeof *colors);
    unsigned int *stack = malloc(g->n * sizeof *stack);

    if (colors == NULL || stack == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        free(colors);
        free(stack);
        return false;
    }

    // -1: não colorido; 0 e 1: cores possíveis.
    for (unsigned int i = 0; i < g->n; i++)
        colors[i] = -1;

    bool bipartite = true;

    // Percorre todas as componentes.
    for (unsigned int i = 0; i < g->n && bipartite; i++) {
        if (colors[i] != -1)
            continue;

        unsigned int top = 0;

        colors[i] = 0;
        stack[top++] = i;

        while (top > 0 && bipartite) {
            unsigned int u = stack[--top];

            for (unsigned int v = 0; v < g->n; v++) {
                if (g->adj[u][v] == 0)
                    continue;

                if (colors[v] == -1) {
                    colors[v] = 1 - colors[u];
                    stack[top++] = v;
                }
                else if (colors[v] == colors[u]) {
                    bipartite = false;
                    break;
                }
            }
        }
    }

    free(colors);
    free(stack);

    return bipartite;
}