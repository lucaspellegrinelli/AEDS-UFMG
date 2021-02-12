#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <chrono>
#include <algorithm>

#include "graph.h"
#include "common.h"
#include "opt.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "You need to indicate a dataset to be used" << std::endl;
    exit(EXIT_SUCCESS);
  }
  
  // Opens the selected dataset
  std::ifstream tsp_dataset(argv[1]);

  // Vector to store each city (x, y) position
  vertice_pos city_positions;

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

  if(dist_type != "EUC_2D" && dist_type != "ATT"){
    std::cout << "Distance function not defined" << std::endl;
    exit(EXIT_SUCCESS);
  }

  // Create problem instance
  TSPInstance tsp_instance(city_positions, dist_type, n_cities);

  // Call the TSP solver and keep track of the time it took to run
  auto start = std::chrono::high_resolution_clock::now(); 
  vertex_list path = tsp(tsp_instance);
  auto stop = std::chrono::high_resolution_clock::now(); 
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

  // Calculate the distance based on the given path
  double distance = evaluate_solution(path, tsp_instance);
  std::cout << distance << "\t" << (duration.count() / 1000000.0) << std::endl;
}