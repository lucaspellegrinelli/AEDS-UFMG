#include "opt.h"

#include <iostream>
#include <algorithm>

#include "common.h"

double reverse_segment_if_better(vertex_list &path, graph_matrix graph, int i, int j, int k){
	std::vector<int> points(6);
	int a = path[i - 1];
	int b = path[i];
	int c = path[j - 1];
	int d = path[j];
	int e = path[k - 1];
	int f = path[k % path.size()];

	double d0 = graph[a][b] + graph[c][d] + graph[e][f];
	double d1 = graph[a][c] + graph[b][d] + graph[e][f];
	double d2 = graph[a][b] + graph[c][e] + graph[d][f];
	double d3 = graph[a][d] + graph[e][b] + graph[c][f];
	double d4 = graph[f][b] + graph[c][d] + graph[e][a];

	if(d0 > d1){
		std::reverse(path.begin() + i, path.begin() + j);
		return d1 - d0;
	}else if(d0 > d2){
		std::reverse(path.begin() + j, path.begin() + k);
		return d2 - d0;
	}else if(d0 > d4){
		std::reverse(path.begin() + i, path.begin() + k);
		return d4 - d0;
	}else if(d0 > d3){
		vertex_list temp;
		temp.insert(temp.end(), path.begin() + j, path.begin() + k);
		temp.insert(temp.end(), path.begin() + i, path.begin() + j);
		for(int x = i; x < k; x++){
			path[x] = temp[x - i];
		}
		return d3 - d0;
	}

	return 0;
}

vertex_list apply_three_opt_optimization(vertex_list path, graph_matrix graph){
  while(true){
		double delta = 0;
		
		for(size_t i = 1; i < graph.size(); i++){
			for(size_t j = i + 2; j < graph.size(); j++){
				for(size_t k = j + 2; k < graph.size() + (i > 0); k++){
					delta += reverse_segment_if_better(path, graph, i, j, k);
				}
			}
		}

		if(delta >= 0) break;
	}

	return path;
}

vertex_list tsp(TSPInstance tsp_instance){
  // Create the adj matrix
  graph_matrix edges(tsp_instance.n_cities, std::vector<double>(tsp_instance.n_cities, 0));

  // Looping through each city combination and computing its distance
  for(size_t ai = 0; ai < tsp_instance.n_cities; ai++){
    auto city_a = tsp_instance.city_positions[ai];
    for(size_t bi = ai + 1; bi < tsp_instance.n_cities; bi++){
      auto city_b = tsp_instance.city_positions[bi];

      double distance = 0;
      if(tsp_instance.dist_type == "EUC_2D"){
        distance = EUC_2D(city_a, city_b);
      }else if(tsp_instance.dist_type == "ATT"){
        distance = ATT(city_a, city_b);
      }

      // Add an edge both ways
      edges[ai][bi] = distance;
      edges[bi][ai] = distance;
    }
  }

  vertex_list path(edges.size());
  for(size_t i = 0; i < edges.size(); i++){
    path[i] = i;
  }

  return apply_three_opt_optimization(path, edges);
}