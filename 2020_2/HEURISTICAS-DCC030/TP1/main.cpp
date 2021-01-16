#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <set>

#include "graph.h"
#include "prim.h"
#include "christofides.h"

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

double evaluate_solution(vertex_list path, std::vector<std::pair<double, double>> city_positions, std::string dist_type){
  // Checking if there are duplicates in the path
  std::set<int> unique_path(path.begin(), path.end());
  bool is_there_duplicates = (unique_path.size() != path.size());

  // Checking if the size of the answer is equal to
  // the number of cities
  bool is_size_ok = (city_positions.size() == unique_path.size()) &&
                    (city_positions.size() == path.size());

  // If there's any problem with the solution, return -1
  if(is_there_duplicates || !is_size_ok){
    return -1;
  }
  
  double distance = 0;
  for(size_t i = 1; i < path.size(); i++){
    auto city_a = city_positions[path[i - 1]];
    auto city_b = city_positions[path[i]];

    if(dist_type == "EUC_2D"){
      distance += EUC_2D(city_a, city_b);
    }else if(dist_type == "ATT"){
      distance += ATT(city_a, city_b);
    }
  }

  return distance;
}

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "You need to indicate a dataset to be used" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Opens the selected dataset
  std::ifstream tsp_dataset(argv[1]);

  // Vector to store each city (x, y) position
  std::vector<std::pair<double, double>> city_positions;

  // Stored which distance type we will use
  std::string dist_type = "EUC_2D";

  // Number of cities to be read
  size_t n_cities = 0;

  // Reads all the (x,y) city positions
  if(tsp_dataset.is_open()){
    std::string line;
    bool city_started = false;
    // For each line, store it in 'line'
    while (std::getline(tsp_dataset, line)){
      if(line == "NODE_COORD_SECTION"){
        // Check if the flag for the start of the city positions
        // was reached in file
        city_started = true;
      }else if(line == "EOF"){
        // Check if we reached the end of the city positions
        break;
      }else if(line.rfind("EDGE_WEIGHT_TYPE", 0) == 0){
        // If we start the line with this, we can get the distance
        // type
        std::istringstream line_stream(line);
        line_stream >> dist_type;
        line_stream >> dist_type;
        if(dist_type == ":"){
          line_stream >> dist_type;
        }
      }else if(line.rfind("DIMENSION", 0) == 0){
        // If we start the line with this, we can get the n_cities
        std::string temp;

        std::istringstream line_stream(line);
        line_stream >> temp;

        while(temp[temp.size() - 1] != ':'){
          line_stream >> temp;
        }

        line_stream >> n_cities;
      }else if(city_started){
        // Create a data stream to get the info about the city
        // represented in the current line and store it in the
        // city vector
        std::istringstream line_stream(line);
        int city_index;
        double city_x, city_y;
        line_stream >> city_index >> city_x >> city_y;
        city_positions.push_back({city_x, city_y});
      }
    }
  }else{
    std::cout << "Couldn't open specified dataset" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // If we read a different amount of cities than the specified
  // amount, we die
  if(city_positions.size() != n_cities){
    std::cout << "Number of cities read different than the number specified in the TSP file" << std::endl;
    exit(EXIT_SUCCESS);
  }

  /// Create the adj matrix
  graph_matrix edges(city_positions.size(), std::vector<double>(city_positions.size(), 0));

  // Looping through each city combination and computing its distance
  for(size_t ai = 0; ai < city_positions.size(); ai++){
    auto city_a = city_positions[ai];
    for(size_t bi = ai + 1; bi < city_positions.size(); bi++){
      auto city_b = city_positions[bi];

      double distance = 0;

      if(dist_type == "EUC_2D"){
        distance = EUC_2D(city_a, city_b);
      }else if(dist_type == "ATT"){
        distance = ATT(city_a, city_b);
      }else{
        distance = EUC_2D(city_a, city_b);
      }

      // Add an edge both ways
      edges[ai][bi] = distance;
      edges[bi][ai] = distance;
    }
  }

  // Call the TSP solver and keep track of the time it took to run
  auto start = std::chrono::high_resolution_clock::now(); 
  vertex_list path = tsp(edges);
  auto stop = std::chrono::high_resolution_clock::now(); 
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

  // Calculate the distance based on the given path
  double distance = evaluate_solution(path, city_positions, dist_type);
  std::cout << distance << "\t" << (duration.count() / 1000000.0) << std::endl;
}