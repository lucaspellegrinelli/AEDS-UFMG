#ifndef TSP_H
#define TSP_H

#include "graph.h"

edge_list find_perfect_matching(vertex_list odd_degrees, graph_matrix edges);
vertex_list create_euler_tour(int start, graph_adj_list adj_list);

vertex_list tsp(graph_matrix edges);

#endif