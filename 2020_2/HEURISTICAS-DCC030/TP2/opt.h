#ifndef OPT3_H
#define OPT3_H

#include "graph.h"
#include "common.h"

double reverse_segment_if_better(vertex_list &path, graph_matrix graph, int i, int j, int k);
vertex_list apply_three_opt_optimization(vertex_list path, graph_matrix graph);

// Runs the heuristic to solve the TSP problem on the given
// graph
vertex_list tsp(TSPInstance tsp_instance);

#endif