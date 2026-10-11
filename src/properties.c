#include <stdlib.h>
#include<stdbool.h> 
#include <stdio.h>
#include "properties.h"

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

    if (visited == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        return false;
    }

    // Aloca uma pilha para percorrer o grafo.
    unsigned int *stack = malloc(g->n * sizeof *stack);

    if (stack == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        free(visited);
        return false;
    }

    unsigned int top = 0;

    // Inicia a busca pelo vértice 0.
    stack[top++] = 0;
    visited[0] = true;

    // Percorre os vértices usando busca em profundidade (DFS).
    while (top > 0) {
        unsigned int u = stack[--top];

        // Procura os vizinhos ainda não visitados.
        for (unsigned int v = 0; v < g->n; v++) {
            if (g->adj[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                stack[top++] = v;
            }
        }
    }

    // Se algum vértice não foi visitado, o grafo é desconexo.
    for (unsigned int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            free(stack);
            free(visited);
            return false;
        }
    }

    // Libera a memória utilizada.
    free(stack);
    free(visited);

    return true;
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
    if (visited == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        return false;
    }

    // Aloca a pilha utilizada na busca em profundidade.
    unsigned int *stack = malloc(g->n * sizeof *stack);
    if (stack == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        free(visited);
        return false;
    }

    // Armazena o vértice predecessor de cada vértice.
    int *parents = malloc(g->n * sizeof *parents);
    if (parents == NULL) {
        fprintf(stderr, "Memória insuficiente!");
        free(stack);
        free(visited);
        return false;
    }

    // Inicializa todos os predecessores como inexistentes.
    for (unsigned int i = 0; i < g->n; i++)
        parents[i] = -1;

    // Percorre todas as componentes do grafo.
    for (unsigned int i = 0; i < g->n; i++) {
        if (visited[i]) continue;

        unsigned int top = 0;

        // Inicia a busca em uma componente não visitada.
        stack[top++] = i;
        visited[i] = true;

        // Explora os vértices da componente atual.
        while (top > 0) {
            unsigned int u = stack[--top];

            for (unsigned int v = 0; v < g->n; v++) {

                // Ignora pares de vértices sem aresta.
                if (g->adj[u][v] == 0)
                    continue;

                // Uma aresta do vértice para ele mesmo (laço) forma um ciclo.
                if (u == v) {
                    free(parents);
                    free(stack);
                    free(visited);
                    return true;
                }

                // Visita o vizinho e registra seu predecessor.
                if (!visited[v]) {
                    visited[v] = true;
                    parents[v] = (int)u;
                    stack[top++] = v;
                }
                // Um vizinho visitado que não é o predecessor
                // indica a existência de um ciclo.
                else if (parents[u] != (int)v) {
                    free(parents);
                    free(stack);
                    free(visited);
                    return true;
                }
            }
        }
    }

    // Libera a memória alocada.
    free(parents);
    free(stack);
    free(visited);

    return false;
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
