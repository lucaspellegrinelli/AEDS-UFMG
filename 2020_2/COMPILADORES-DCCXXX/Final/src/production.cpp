#include "production.h"

#include <iostream>
#include <const.h>

Production::Production(int left, std::vector<int> right){
  this->index = -1;
  this->left = left;
  this->right = right;
  this->marker = 0;
}

void Production::set_index(int index){
  this->index = index;
}

void Production::print(){
  std::cout << token_type_to_str(this->left) << " ->";
  for(int i : right){
    std::cout << " " << token_type_to_str(i);
  }

  std::cout << std::endl;
}

void Production::print_with_marker(){
  std::cout << "\t" << token_type_to_str(this->left) << "->";

  int c = 0;
  for(int i : right) {
    if (marker == c){
      std::cout << " •" ;
    }

    c++;
    std::cout << " " << token_type_to_str(i);
  }

  if(marker == right.size()){
      std::cout << " •" ;
  }

  std::cout << std::endl;
}