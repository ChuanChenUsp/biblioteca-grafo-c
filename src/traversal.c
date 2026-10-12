/**
 * @file traversal.c
 * @brief Percursos em grafos: alcançabilidade, tamanho de componente e distância.
 */

#include <stdlib.h>
#include <stdio.h>
#include "traversal.h"
#include <limits.h>
#define INF INT_MAX


/**
 * @brief DFS recursiva que procura o vértice @p destino a partir de @p atual.
 *
 * @param g        Grafo (matriz de adjacência).
 * @param atual    Vértice sendo visitado.
 * @param destino  Vértice procurado.
 * @param visitado Vetor de n posições; visitado[i] é true se i já foi visitado.
 * @return true se @p destino é alcançável a partir de @p atual.
 */
static bool dfs_reach(const Graph *g, unsigned int atual, unsigned int destino, bool *visitado){
    if (atual == destino) return true;
    visitado[atual] = true;                      // marca antes de explorar os vizinhos
    for (unsigned int i = 0; i < g->n; i++){
        if (g->adj[atual][i] != 0 && !visitado[i])
            if(dfs_reach(g, i, destino, visitado)) return true;

    }
    return false;
}

/**
 * @brief DFS recursiva que conta os vértices alcançáveis a partir de @p atual.
 *
 * @param g          Grafo (matriz de adjacência).
 * @param atual      Vértice sendo visitado.
 * @param visitado   Vetor de n posições; visitado[i] é true se i já foi visitado.
 * @param componente Contador compartilhado por todas as chamadas recursivas.
 */
static void dfs_component(const Graph *g, unsigned int atual, bool *visitado, int *componente){
    visitado[atual] = true;
    (*componente)++;                             // conta ao entrar, inclusive o inicial
    for (unsigned int i = 0; i < g->n; i++)
        if (g->adj[atual][i] != 0 && !visitado[i])
            dfs_component(g, i, visitado, componente);
    return;
}


/**
 * @brief Verifica se @p v é alcançável a partir de @p u.
 *
 * Todo vértice alcança a si mesmo (u == v devolve true).
 *
 * @param g Grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 * @return true se existe caminho de @p u até @p v; false caso contrário,
 *         ou se @p g for NULL, algum vértice for inválido ou faltar memória.
 */
bool graph_is_reachable(const Graph *g, unsigned int u,unsigned int v){
    if (g == NULL || ( u >= g->n) || (v >= g->n)) return false;
    bool *visited = calloc(g->n, sizeof *visited);     // tudo false
    if (visited == NULL) {
        free(visited);
        fprintf(stderr, "Memória insuficiente!\n");
        return false;
    }
    bool answer = dfs_reach(g, u, v, visited);
    free(visited);                               // libera antes do return
    return answer;
}

/**
 * @brief Tamanho da componente conexa que contém @p u (inclui o próprio @p u).
 *
 * @param g Grafo.
 * @param u Vértice de referência.
 * @return Número de vértices da componente; 0 se @p g for NULL,
 *         @p u for inválido ou faltar memória.
 */
int graph_component_size(const Graph *g, unsigned int u){
    if (g == NULL || (u >= g->n)) return 0;
    int value = 0;
    int *p = &value;
    bool *visited = calloc(g->n, sizeof *visited);
    if (visited == NULL){
        free(visited);
        fprintf(stderr, "Memória insuficiente!\n");
        return -1;
    }
    dfs_component(g, u, visited, p);
    free(visited);
    return value;
}

/**
 * @brief Menor distância de @p u até @p v, medida em número de arestas.
 *
 * Usa BFS; os pesos das arestas são ignorados.
 * Custo: O(n^2) de tempo e O(n) de memória extra.
 *
 * @param g Grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 * @return 0 se u == v; a distância (>= 1) se @p v é alcançável; -1 se @p g for NULL,
 *         algum vértice for inválido, @p v for inalcançável ou faltar memória.
 */
int graph_distance_length(const Graph *g, unsigned int u, unsigned int v){
    if(g == NULL || u >= g->n || v >= g->n) return -1;

    // dist[i]: distância de u até i (-1 = ainda não descoberto)
    // fila:    vértices descobertos, na ordem em que serão processados
    int *dist = malloc(g->n * sizeof *dist);
    unsigned int *fila = malloc(g->n * sizeof *fila);
    if(dist == NULL || fila == NULL){
        free(dist);                              // free(NULL) é permitido
        free(fila);
        fprintf(stderr, "Memória insuficiente!\n");
        return -1;
    }

    for(unsigned int i = 0; i < g->n; i++){
        dist[i] = -1;
    }

    // a origem está a distância 0 e é a primeira da fila
    unsigned int inicio = 0;
    unsigned int fim = 0;
    dist[u] = 0;
    fila[fim++] = u;
        
    // bfs

    while(inicio < fim){
        unsigned int atual = fila[inicio++];
        if(atual == v) break;                    // dist[v] já é a menor

        for(unsigned int i = 0; i < g->n; i++){
            if(g->adj[atual][i] != 0 && dist[i] == -1){
                dist[i] = dist[atual] + 1;
                fila[fim++] = i;
            }
        }
    }

    int resultado = dist[v];
    free(dist);
    free(fila);
    return resultado;
}
/**
 * @brief Menor distância de @p u até @p v, medida pela soma dos pesos das arestas.
 *
 * Usa o algoritmo de Dijkstra, que exige pesos não negativos (garantido aqui:
 * o peso é unsigned e 0 significa "sem aresta"). Para a distância em número
 * de arestas, veja graph_distance_lenght().
 *
 * @param g Grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 * @return 0 se u == v; a soma dos pesos do caminho mais barato se @p v é alcançável;
 *         -1 se @p g for NULL, algum vértice for inválido, @p v for inalcançável
 *         ou faltar memória.
 * @note Custo: O(n^2) de tempo e O(n) de memória extra.
 * @warning Assume que a soma dos pesos do caminho cabe em int.
 * @see graph_distance_lenght
 */
int graph_distance_weight(const Graph *g, unsigned int u, unsigned int v){
    if(g == NULL || u >= g->n || v >= g->n) return -1;  

    int *dist = malloc(g->n * sizeof *dist);
    bool *done = calloc(g->n, sizeof *done);
    if(dist == NULL || done == NULL){
        free(dist); free(done);
        fprintf(stderr, "Memória insuficiente \n");
        return -1;
    }

    for(unsigned int i = 0; i < g->n; i++) dist[i] = INF;
    dist[u] = 0;

// Algoritmo de Dijkstra: escolhemos o caminho mais curto atual e atualizamos todos os valores dos outros vertices à ele.

    for(unsigned int passo = 0; passo < g->n; passo++){
        // simulação de fila de prioridade.
        unsigned int x = 0;
        int melhor = INF;
        for(unsigned int i = 0; i < g->n; i++){
            if( !done[i] && dist[i] < melhor){      
                melhor = dist[i];
                x = i;
            }
        }
        if (melhor == INF) break;                    // o resto é inalcançável

        done[x] = true;                             
        if(x == v) break;

        for(unsigned int y = 0; y < g->n; y++){         //  Passar por x melhora o custo de y?
            if( g->adj[x][y] != 0 && !done[y]){         
                int nova = dist[x] + (int)g->adj[x][y];      
                if (nova < dist[y]) dist[y] = nova;
            }
        }
    }

    int resultado = (dist[v] == INF) ? -1 : dist[v];
    free(dist);
    free(done);
    return resultado;
}
