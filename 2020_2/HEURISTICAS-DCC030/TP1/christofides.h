#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H

#include <string>

#include "graph.h"
#include "common.h"

// Creates an euler tour from the given starting point
// and the adjencency list of the graph
vertex_list create_euler_tour(int start, graph_adj_list adj_list);

// Runs the heuristic to solve the TSP problem on the given
// graph
vertex_list tsp(TSPInstance tsp_instance);

#endif