/**
 * @file properties.c
 * @brief Implementação de funções para verificar propriedades de grafos.
 */


#include <stdlib.h>
#include <stdbool.h> 
#include <stdio.h>
#include "properties.h"

/**
 * @brief Visita todos os vértices alcançáveis a partir de um vértice inicial.
 *
 * @param g Ponteiro constante para o grafo.
 * @param start Índice do vértice inicial da busca.
 * @param visited Vetor que indica os vértices já visitados.
 * @param stack Pilha utilizada para armazenar os vértices a processar.
 *
 * @note Esta é uma função auxiliar privada deste arquivo.
 * @pre O grafo e os vetores devem ser válidos, e start deve ser um
 *      índice válido de vértice.
 */
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

/**
 * @brief Verifica se existe um ciclo em uma componente do grafo.
 *
 * @param g Ponteiro constante para o grafo.
 * @param start Índice do vértice inicial da busca.
 * @param visited Vetor que indica os vértices já visitados.
 * @param stack Pilha utilizada para armazenar os vértices a processar.
 * @param parents Vetor que armazena o predecessor de cada vértice.
 *                O valor -1 indica ausência de predecessor.
 *
 * @return true se for encontrado um ciclo; false caso contrário.
 *
 * @note Esta é uma função auxiliar privada deste arquivo.
 * @pre O grafo e os vetores devem ser válidos, e start deve ser um
 *      índice válido de vértice.
 */
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

/**
 * @brief Verifica se o grafo é conexo.
 *
 * @param g Ponteiro constante para o grafo a ser verificado.
 *
 * @return true se o grafo for conexo; false se não for conexo,
 *         se g for NULL ou se ocorrer uma falha de alocação.
 *
 * @note A função imprime uma mensagem de erro em stderr quando
 *       o grafo não está inicializado ou ocorre uma falha de alocação.
 */
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

/**
 * @brief Verifica se o grafo possui algum ciclo.
 *
 * @param g Ponteiro constante para o grafo a ser verificado.
 *
 * @return true se o grafo possuir pelo menos um ciclo; false se não
 *         possuir ciclos, se g for NULL ou se ocorrer uma falha
 *         de alocação.
 *
 * @note A função imprime uma mensagem de erro em stderr quando
 *       o grafo não está inicializado ou ocorre uma falha de alocação.
 *
 */
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

/**
 * @brief Verifica se o grafo é uma árvore.
 *
 * Um grafo não direcionado é uma árvore quando é conexo e não
 * possui ciclos.
 *
 * A função combina os resultados das funções
 * @ref graph_is_connected e @ref graph_has_cycle.
 *
 * @param g Ponteiro constante para o grafo a ser verificado.
 *
 * @return true se o grafo for uma árvore; false caso contrário.
 *
 * @note Como um grafo vazio é considerado conexo, mas não possui
 *       ciclos, esta implementação considera o grafo vazio uma árvore.
 *
 */
bool graph_is_tree(const Graph *g) {
    return graph_is_connected(g) && !graph_has_cycle(g);
}

/**
 * @brief Verifica se o grafo é uma floresta.
 *
 * Uma floresta é um grafo não direcionado que não possui ciclos.
 * Ela pode conter várias componentes conexas.
 *
 * A função verifica a ausência de ciclos por meio da função
 * @ref graph_has_cycle.
 *
 * @param g Ponteiro constante para o grafo a ser verificado.
 *
 * @return true se o grafo não possuir ciclos; false caso contrário.
 *
 * @note Se g for NULL, a função retorna false.
 * @note Uma falha de alocação em graph_has_cycle também resulta em
 *       false, pois a função não distingue erro de ausência de ciclos.
 *
 */
bool graph_is_forest(const Graph *g) {
    if (g == NULL) {
        fprintf(stderr, "Grafo não inicializado!");
        return false;
    }

    return !graph_has_cycle(g);
}

/**
 * @brief Verifica se o grafo é bipartido.
 *
 * Um grafo é bipartido quando seus vértices podem ser divididos
 * em dois conjuntos disjuntos, de modo que cada aresta conecte
 * vértices pertencentes a conjuntos diferentes.
 *
 * A função utiliza uma busca em profundidade iterativa e atribui
 * uma de duas cores a cada vértice. Se dois vértices adjacentes
 * receberem a mesma cor, o grafo não é bipartido.
 *
 * Todas as componentes do grafo são verificadas.
 *
 * Um grafo vazio é considerado bipartido por esta implementação.
 *
 * @param g Ponteiro constante para o grafo a ser verificado.
 *
 * @return true se o grafo for bipartido; false se não for bipartido,
 *         se g for NULL ou se ocorrer uma falha de alocação.
 *
 * @note A função imprime uma mensagem de erro em stderr quando
 *       o grafo não está inicializado ou ocorre uma falha de alocação.
 *
 */
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