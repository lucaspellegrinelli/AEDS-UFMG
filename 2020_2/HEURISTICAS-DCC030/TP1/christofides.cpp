#include "christofides.h"

#include <stack>
#include <limits>
#include <vector>
#include <utility>
#include <iostream>

#include "graph.h"
#include "prim.h"
#include "mwpm.h"

vertex_list create_euler_tour(int start, graph_adj_list adj_list){
  // Start the tour with the start vertice
  vertex_list path;
  path.push_back(start);

  std::stack<int> stack;
  int current_v = start;

  // While we still have vertices on the open list
  while(!stack.empty() || adj_list[current_v].size() > 0){
    // If the current vertice has no more unvisited neighbors
    if(adj_list[current_v].empty()){
      // We add it to the final path
      path.push_back(current_v);

      // Get the next vertice from the stack
      current_v = stack.top();
      stack.pop();
    } else{
      // If there are still neighbors to be visited...
      stack.push(current_v);

      // The next vertice will be retrieved from the current
      // vertice neighbor list
      int next_v = adj_list[current_v].back();
      adj_list[current_v].pop_back();

      // We remove the current vertice from the next vertice
      // adjecency list so it won't come back to the current
      // vertice
      for(size_t i = 0; i < adj_list[next_v].size(); i++){
        if(adj_list[next_v][i] == current_v){
          adj_list[next_v].erase(adj_list[next_v].begin() + i);
        }
      }

      // Next iteration we update the vertice
      current_v = next_v;
    }
  }
  
  path.push_back(current_v);

  // Removed duplicated vertices from the tour
  std::vector<bool> visited(path.size(), false);
  vertex_list tour;

  for(int v : path){
    if(!visited[v]){
      visited[v] = true;
      tour.push_back(v);
    }
  }

  return tour;
}

vertex_list tsp(graph_matrix edges){
  // Calculating the minimum spanning tree from the graph
  edge_list mst = min_spanning_tree(edges);

  // Creates an adjecency list from the min spanning tree
  graph_adj_list adj_list(edges.size(), vertex_list());
  for(auto a : mst){
    adj_list[a.first].push_back(a.second);
    adj_list[a.second].push_back(a.first);
  }

  // Get the vertices with and odd degree
  vertex_list odd_degrees;
  for(int v = 0; v < (int)edges.size(); v++){
    if(adj_list[v].size() % 2 == 1){
      odd_degrees.push_back(v);
    }
  }

  // Creates the "perfect" matching for the odd degree vertices
  edge_list matching = find_min_weight_perfect_matching(odd_degrees, edges);

  // Add the new edges to the adjecency list
  for(auto m : matching){
    adj_list[m.first].push_back(m.second);
    adj_list[m.second].push_back(m.first);
  }

  int best_start = 0;
  double best_distance = std::numeric_limits<double>::max();

  // Loop through every possible starting point
	for (size_t s = 0; s < adj_list.size(); s++) {
    // Calculates the euler tour starting from the
    // current starting point
		vertex_list path = create_euler_tour(s, adj_list);

    // Calculates the tour distance
    double distance = 0;
    for(size_t i = 0; i < path.size() - 1; i++){
      distance += edges[path[i]][path[i + 1]];
    }

    // If this is the best distance, save it
		if (distance < best_distance) {
			best_start = s;
			best_distance = distance;
		}
	}

  // Returns the tour with minimum distance
  return create_euler_tour(best_start, adj_list);
}