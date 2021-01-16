#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H

#include "graph.h"

vertex_list create_euler_tour(int start, graph_adj_list adj_list);
vertex_list tsp(graph_matrix edges);

#endif