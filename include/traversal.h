#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <stdbool.h>
#include "core.h"

// verifica se v é alcançável a partir de u
bool graph_is_reachable(const Graph *g, unsigned int u, unsigned int v);

// retorna o tamanho da componente conexa de u (0 se g for NULL ou u for inválido)
int graph_component_size(const Graph *g, unsigned int u);

// retorna a menor distância de u até v em número de arestas (-1 se não existe caminho ou entrada inválida)
int graph_distance_length(const Graph *g, unsigned int u, unsigned int v);

// retorna a menor distância de u até v pela soma dos pesos (-1 se não existe caminho ou entrada inválida)
int graph_distance_weight(const Graph *g, unsigned int u, unsigned int v);

// retorna um array com a distância (soma dos pesos) de u até cada vértice (-1 se inalcançável); NULL em caso de erro; liberar com free()
int *graph_all_distances(const Graph *g, unsigned int u);

// retorna um array com a distância (em arestas) de u até cada vértice (-1 se inalcançável); NULL em caso de erro; liberar com free()
int *graph_all_distances_length(const Graph *g, unsigned int u);

#endif
