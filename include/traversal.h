#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <stdbool.h>
#include "core.h"

/**
 * @brief Verifica se um vértice é alcançável a partir de outro.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 *
 * @return true se v for alcançável a partir de u; false caso contrário
 *         ou se os parâmetros forem inválidos.
 */
bool graph_is_reachable(const Graph *g, unsigned int u, unsigned int v);

/**
 * @brief Calcula o tamanho da componente conexa de um vértice.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de referência.
 *
 * @return Número de vértices da componente conexa de u, ou 0 se g for NULL
 *         ou u for inválido.
 */
int graph_component_size(const Graph *g, unsigned int u);

/**
 * @brief Calcula a menor distância entre dois vértices em número de arestas.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 *
 * @return Menor número de arestas entre u e v, ou -1 se não existir caminho
 *         ou se a entrada for inválida.
 */
int graph_distance_length(const Graph *g, unsigned int u, unsigned int v);

/**
 * @brief Calcula a menor distância ponderada entre dois vértices.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 *
 * @return Menor custo total do caminho entre u e v, ou -1 se não existir
 *         caminho ou se a entrada for inválida.
 */
int graph_distance_weight(const Graph *g, unsigned int u, unsigned int v);

/**
 * @brief Calcula as menores distâncias em número de arestas a partir de um vértice.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem.
 *
 * @return Ponteiro para um array com a distância mínima até cada vértice,
 *         usando -1 para vértices inalcançáveis; NULL em caso de erro.
 *
 * @note O array retornado deve ser liberado com free().
 */
int *graph_distance_length_all(const Graph *g, unsigned int u);

/**
 * @brief Calcula as menores distâncias ponderadas a partir de um vértice.
 *
 * @param g Ponteiro para o grafo.
 * @param u Vértice de origem.
 *
 * @return Ponteiro para um array com a distância ponderada mínima até cada
 *         vértice, usando -1 para vértices inalcançáveis; NULL em caso de erro.
 *
 * @note O array retornado deve ser liberado com free().
 */
int *graph_distance_weight_all(const Graph *g, unsigned int u);

#endif