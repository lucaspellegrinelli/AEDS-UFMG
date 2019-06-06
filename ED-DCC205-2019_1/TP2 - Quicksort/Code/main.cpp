#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "sort_request.hpp"
int a(int b){
  return 1;
}
int main(int argc, char *argv[]){
  srand (time(NULL));
  SortRequest sr = SortRequest(argv[1], argv[2], argv[3], argc > 4);
  sr.run();

  return 0;
}
