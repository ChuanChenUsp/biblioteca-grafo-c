
#ifndef EDGES_H
#include<stdlib.h>
#include<stdbool.h> 
#include "core.h"
#define EDGES_H


/**
 * @brief Adiciona uma aresta entre vértices @p u e @p v.
 *
 * @param g        Ponteiro para o grafo.
 * @param u        Primeiro vértice.
 * @param v        Segundo vértice.
 * @param w        Peso da aresta.
 * @return true em caso de sucesso, false em caso de erro.
 * 
 * @note A quantidade de aresta será mudado correspondentemente.
 * @note substitui, caso existe, a aresta original entre @p u e @p v.
 */
bool graph_add_edge(Graph *g, unsigned int u, unsigned int v, unsigned int w);

/**
 * @brief Remove a aresta entre vértices @p u e @p v.
 *
 * @param g        Ponteiro para o grafo.
 * @param u        Primeiro vértice.
 * @param v        Segundo vértice.
 * @param w        Peso da aresta.
 * @return true em caso de sucesso, false em caso de erro.
 * 
 * @note A quantidade de aresta será mudado correspondentemente.
 */
bool graph_remove_edge(Graph *g, unsigned int u,unsigned int v);

/**
 * @brief Obter o peso entre vértices @p u e @p v.
 *
 * @param g        Ponteiro para o grafo.
 * @param u        Primeiro vértice.
 * @param v        Segundo vértice.
 * @return Peso da aresta. 0 se ela não existe.
 */
int graph_get_weight(const Graph *g, unsigned int u, unsigned int v);

/**
 * @brief Obter todas as arestas do grafo apontado pelo @p g.
 *
 * @param g        Ponteiro para o grafo.
 * @param count    Ponteiro onde será armazenada a quantidade de arestas.
 * @return Vetor de arestas ou NULL em caso de erro.
 */
Edge *graph_get_edges(const Graph *g, int *count);

/**
 * @brief Retorna o grau do vértice @p u.
 *
 * Em grafos não direcionados, 
 *
 * @param g Grafo.
 * @param u Vértice consultado.
 * @return Grau do vértice. -1 Em caso de erro.
 * @note Um laço contribui com 2 para o grau.
 */
int graph_degree(const Graph *g, unsigned int u); // retorna o grau do vértice u
    
#endif                         
