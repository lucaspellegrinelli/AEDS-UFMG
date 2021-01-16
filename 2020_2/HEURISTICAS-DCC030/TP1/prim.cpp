#include "prim.h"

#include <iostream>
#include <functional>
#include <limits>
#include <vector>
#include <utility>

#include "graph.h"

edge_list min_spanning_tree(graph_matrix edges){
  // Vector representing which component each node is in
  std::vector<int> parents(edges.size());
  std::vector<double> key(edges.size());
  std::vector<bool> in_mst(edges.size());

  // Finds the vertex with minimum key value
  std::function<int(void)> find_min_key = [&](){
    double min = std::numeric_limits<double>::max();
    int min_index = -1;

    // Find the vertice not on the min spanning tree
    // with minimal key value
    for(size_t v = 0; v < edges.size(); v++){
      if(!in_mst[v] && key[v] < min){
        min = key[v];
        min_index = v;
      }
    }

    return min_index;
  };

  // Starts all keys with infinity
  for(size_t v = 0; v < edges.size(); v++){
    key[v] = std::numeric_limits<double>::max();
    in_mst[v] = false;
  }

  // Make key 0 so that this vertex is picked as first vertex.
  key[0] = 0;
  parents[0] = -1;
  
  for(size_t count = 0; count < edges.size() - 1; count++){
    // Gets the vertice with minimum key
    int u = find_min_key();

    // Add it to the min spanning tree
    in_mst[u] = true;

    // For each other vertice
    for(size_t v = 0; v < edges.size(); v++){
      // If it is not on the mst, has a connection to 'u' and this connection
      // has weight smaller than the current 'v' key
      if(edges[u][v] > 0 && !in_mst[v] && edges[u][v] < key[v]){
        // Add 'u' to the subset of 'v' and update its key
        parents[v] = u;
        key[v] = edges[u][v];
      }
    }
  }

  // Add each edge to the final answer
  edge_list min_spanning_tree;
  for(size_t i = 1; i < edges.size(); i++){
    min_spanning_tree.push_back({parents[i], i});
  }

  return min_spanning_tree;
}