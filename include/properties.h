#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <stdbool.h>
#include "core.h"

/**
 * @file properties.h
 * @brief Declara funções para verificar propriedades de grafos.
 *
 * Este módulo disponibiliza funções para verificar conectividade,
 * ciclos, árvores, florestas e bipartição em grafos.
 */

/**
 * @brief Verifica se o grafo é conexo.
 *
 * Um grafo é conexo quando todos os seus vértices são alcançáveis
 * a partir de qualquer vértice.
 *
 * @param g Ponteiro para o grafo a ser verificado.
 * @return true se o grafo for conexo; false caso contrário.
 */
bool graph_is_connected(const Graph *g);

/**
 * @brief Verifica se o grafo possui ciclos.
 *
 * @param g Ponteiro para o grafo a ser verificado.
 * @return true se o grafo possuir pelo menos um ciclo;
 *         false caso contrário.
 */
bool graph_has_cycle(const Graph *g);

/**
 * @brief Verifica se o grafo é uma árvore.
 *
 * Um grafo é uma árvore quando é conexo e não possui ciclos.
 *
 * @param g Ponteiro para o grafo a ser verificado.
 * @return true se o grafo for uma árvore; false caso contrário.
 */
bool graph_is_tree(const Graph *g);

/**
 * @brief Verifica se o grafo é uma floresta.
 *
 * Uma floresta é um grafo que não possui ciclos.
 *
 * @param g Ponteiro para o grafo a ser verificado.
 * @return true se o grafo não possuir ciclos; false caso contrário.
 */
bool graph_is_forest(const Graph *g);

/**
 * @brief Verifica se o grafo é bipartido.
 *
 * Um grafo é bipartido quando seus vértices podem ser divididos
 * em dois conjuntos, de modo que toda aresta conecte vértices
 * de conjuntos diferentes.
 *
 * @param g Ponteiro para o grafo a ser verificado.
 * @return true se o grafo for bipartido; false caso contrário.
 */
bool graph_is_bipartite(const Graph *g);

#endif 