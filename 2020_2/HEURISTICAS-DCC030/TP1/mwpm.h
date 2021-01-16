#ifndef MWPM_H
#define MWPM_H

#include "graph.h"

// Runs the heuristic to find the minimum weights
// perfect matching of the vertices given to it
edge_list find_min_weight_perfect_matching(vertex_list odd_degrees, graph_matrix edges);

#endif