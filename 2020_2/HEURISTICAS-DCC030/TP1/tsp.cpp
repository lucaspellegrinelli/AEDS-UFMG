#include "tsp.h"
#include "graph.h"
#include "prim.h"

#include <limits>
#include <stack>
#include <vector>
#include <utility>

edge_list find_perfect_matching(vertex_list odd_degrees, graph_matrix edges){
  edge_list matching;
  
  // While we still have odd_degree vertices
  while(odd_degrees.size() > 0){
    // Select the first odd degree vertice
    int vert_a = odd_degrees[0];

    int best_match = -1;
    int best_match_i = -1;
    double best_dist = std::numeric_limits<double>::max();

    // Find the closest odd degree vertice to the first odd
    //degree vertice
    for(size_t i = 1; i < odd_degrees.size(); i++){
      int vert_b = odd_degrees[i];
      if(edges[vert_a][vert_b] < best_dist){
        best_match = vert_b;
        best_match_i = i;
        best_dist = edges[vert_a][vert_b];
      }
    }

    // Add the connection between the first odd degree vertice
    // and the closest odd degree vertice to it and remove
    // both from the list
    matching.push_back({vert_a, best_match});
    odd_degrees.erase(odd_degrees.begin() + best_match_i);
    odd_degrees.erase(odd_degrees.begin());
  }

  return matching;
}

vertex_list create_euler_tour(int start, graph_adj_list adj_list){
  // Start the tour with the start vertice
  vertex_list path;
  path.push_back(start);

  std::stack<int> stack;
  int current_v = start;
  path.push_back(start);
  while(!stack.empty() || adj_list[current_v].size() > 0){
    if(adj_list[current_v].empty()){
      path.push_back(current_v);
      current_v = stack.top();
      stack.pop();
    }
    else{
      stack.push(current_v);
      int next_v = adj_list[current_v].back();
      adj_list[current_v].pop_back();

      for(size_t i = 0; i < adj_list[next_v].size(); i++){
        if(adj_list[next_v][i] == current_v){
          adj_list[next_v].erase(adj_list[next_v].begin()+i);
        }
      }

      current_v = next_v;
    }
  }
  
  path.push_back(current_v);

  std::vector<bool> visited(path.size(), false);
  vertex_list tour;

  // Removed duplicated vertices from the tour
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

  // Gets a minimum perfect matching for these odd degree
  // vertices
  edge_list matching = find_perfect_matching(odd_degrees, edges);

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