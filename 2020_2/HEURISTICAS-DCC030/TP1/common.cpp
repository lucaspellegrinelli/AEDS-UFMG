#include "common.h"

#include <vector>
#include <utility>
#include <string>
#include <set>
#include <cmath>

#include "graph.h"

double EUC_2D(std::pair<double, double> city_a, std::pair<double, double> city_b){
  double x_distance = std::abs(city_a.first - city_b.first);
  double y_distance = std::abs(city_a.second - city_b.second);
  double distance = std::sqrt(std::pow(x_distance, 2) + std::pow(y_distance, 2));
  return std::round(distance);
}

double ATT(std::pair<double, double> city_a, std::pair<double, double> city_b){
  double x_distance = std::abs(city_a.first - city_b.first);
  double y_distance = std::abs(city_a.second - city_b.second);
  double distance = std::sqrt((std::pow(x_distance, 2) + std::pow(y_distance, 2)) / 10.0);
  int distance_i = std::round(distance);

  if(distance_i < distance){
    return distance_i + 1;
  }else{
    return distance_i;
  }
}

double evaluate_solution(vertex_list path, TSPInstance tsp_instance){
  // Checking if there are duplicates in the path
  std::set<int> unique_path(path.begin(), path.end());
  bool is_there_duplicates = (unique_path.size() != path.size());

  // Checking if the size of the answer is equal to
  // the number of cities
  bool is_size_ok = (tsp_instance.n_cities == unique_path.size()) &&
                    (tsp_instance.n_cities == path.size());

  // If there's any problem with the solution, return -1
  if(is_there_duplicates || !is_size_ok){
    return -1;
  }
  
  double distance = 0;
  for(size_t i = 1; i < path.size(); i++){
    auto city_a = tsp_instance.city_positions[path[i - 1]];
    auto city_b = tsp_instance.city_positions[path[i]];

    if(tsp_instance.dist_type == "EUC_2D"){
      distance += EUC_2D(city_a, city_b);
    }else if(tsp_instance.dist_type == "ATT"){
      distance += ATT(city_a, city_b);
    }else{
      // If the distance type is unknown, return -2
      return -2;
    }
  }

  return distance;
}