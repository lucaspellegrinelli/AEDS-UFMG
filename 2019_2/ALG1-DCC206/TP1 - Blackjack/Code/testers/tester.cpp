#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define ITERATION_COUNT 1

int main(int argc, char *argv[]){
  if(argc < 3){
    std::cout << "Passe para o programa o caminho para o executável e o caminho para o teste";
  }

  string comm = argv[1];
  comm.append(" ");
  comm.append(argv[2]);

  char comm_arr[comm.size() + 1];
  strcpy(comm_arr, comm.c_str());

  auto start = high_resolution_clock::now();

  for(int i = 0; i < ITERATION_COUNT; i++){
    std::system(comm_arr);
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  cout << duration.count() / ITERATION_COUNT << " milliseconds" << endl;

  return 0;
}
