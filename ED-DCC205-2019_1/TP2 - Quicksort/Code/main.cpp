#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "sort_request.hpp"

using namespace std;

int main(int argc, char *argv[]){
  SortRequest sr = SortRequest(argv[1], argv[2], argv[3], argc > 4);
  sr.run();

  return 0;
}
