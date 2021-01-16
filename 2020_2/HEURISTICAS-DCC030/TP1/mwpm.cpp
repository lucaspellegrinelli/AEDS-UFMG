#include "mwpm.h"

#include <limits>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

#include "graph.h"

edge_list find_min_weight_perfect_matching(vertex_list odd_degrees, graph_matrix edges){
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

  // Works like a bubble sort.
  // Loops through each pair of matchings and permutate which
  // vertices are connected in that pair. Then with all 4
  // permutations, get the one with minimum summed weight
  // and replace the matchings with that one
  for(size_t c = 0; c < matching.size(); c++){
    for(size_t i = 1; i < matching.size(); i++){
      int j = i - 1;

      // Stores the distances for each of the permutations
      std::vector<std::pair<double, double>> distances{
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
      };

      // Stores the vertices in each permutation
      std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> matches{
        {{matching[i].first, matching[i].second}, {matching[j].first, matching[j].second}},
        {{matching[i].first, matching[j].second}, {matching[j].first, matching[i].second}},
        {{matching[j].first, matching[i].second}, {matching[i].first, matching[j].second}},
        {{matching[j].first, matching[j].second}, {matching[i].first, matching[i].second}}
      };

      // Calculates the distance for each permutation
      for(size_t k = 0; k < matches.size(); k++){
        distances[k].first = edges[matches[k].first.first][matches[k].first.second];
        distances[k].second = edges[matches[k].second.first][matches[k].second.second];
      }

      int min_dist_i = 0;
      double min_dist = std::numeric_limits<double>::max();
      // Finds the permutation with less combined distance
      for(size_t k = 1; k < matches.size(); k++){
        if((distances[k].first + distances[k].second) < min_dist){
          min_dist_i = k;
          min_dist = distances[k].first + distances[k].second;
        }
      }

      // Replace the matching with the best one found
      matching[i].first = matches[min_dist_i].first.first;
      matching[i].second = matches[min_dist_i].first.second;
      matching[j].first = matches[min_dist_i].second.first;
      matching[j].second = matches[min_dist_i].second.second;
    }
  }

  return matching;
}