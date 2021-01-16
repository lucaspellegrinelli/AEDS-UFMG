#ifndef OPT_H
#define OPT_H

#include "graph.h"

double reverse_segment_if_better(vertex_list &path, graph_matrix graph, int i, int j, int k);
vertex_list apply_three_opt_optimization(vertex_list path, graph_matrix graph);

#endif