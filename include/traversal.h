#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <stdbool.h>
#include "core.h"

// verifica se v é alcançável a partir de u
bool graph_is_reachable(const Graph *g, unsigned int u, unsigned int v);

#endif
