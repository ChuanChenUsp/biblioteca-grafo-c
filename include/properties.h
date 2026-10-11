#ifndef PROPERTIES_H
#define PROPERTIES_H

#include<stdlib.h>
#include<stdbool.h> 
#include "core.h"

bool graph_is_connected(const Graph *g); 
bool graph_has_cycle(const Graph *g); 
bool graph_is_tree(const Graph *g); 
bool graph_is_forest(const Graph *g); 

#endif