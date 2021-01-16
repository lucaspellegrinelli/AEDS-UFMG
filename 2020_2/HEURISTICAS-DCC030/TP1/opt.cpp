#include "opt.h"

#include <iostream>
#include <algorithm>

double reverse_segment_if_better(vertex_list &path, graph_matrix graph, int i, int j, int k){
	std::vector<int> points(6);
	int a = path[i - 1];
	int b = path[i];
	int c = path[j - 1];
	int d = path[j];
	int e = path[k - 1];
	int f = path[k];

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