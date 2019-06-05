#include <iostream>
#include "quicksort.hpp"

using namespace std;

int main(){
  Quicksort qs = new Quicksort();

  int size = 5;
  int arr[size] = {4, 7, 2, 5, 8};

  qs.sort(arr, 0, size - 1, "QPE");

  for(int i = 0; i < size; i++){
    cout << arr[i] << endl;
  }
  
  return 0;
}
