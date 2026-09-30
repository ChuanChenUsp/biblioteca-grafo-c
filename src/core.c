#include "core.h"
Graph *graph_create(size_t n);
void graph_destroy(Graph *g);
size_t graph_get_vertices(const Graph *g);
Edge *graph_get_edges(const Graph *g, size_t *count);


