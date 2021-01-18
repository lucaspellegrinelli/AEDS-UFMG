#ifndef COMMON_H
#define COMMON_H

#include <string>

#include "graph.h"

class TSPInstance{
  public:
  vertice_pos city_positions;
  std::string dist_type;
  size_t n_cities;

  TSPInstance(vertice_pos city_positions, std::string dist_type, int n_cities){
    this->city_positions = city_positions;
    this->dist_type = dist_type;
    this->n_cities = n_cities;

    if(this->n_cities != city_positions.size()){
      this->n_cities = -1;
    }
  }
};

double EUC_2D(std::pair<double, double> city_a, std::pair<double, double> city_b);
double ATT(std::pair<double, double> city_a, std::pair<double, double> city_b);

double evaluate_solution(vertex_list path, TSPInstance tsp_instance);

#endif