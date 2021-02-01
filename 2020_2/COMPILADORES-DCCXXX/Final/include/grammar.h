#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include "production.h"

class Grammar{
public:
  std::vector<Production> productions;

  Grammar();
  
  void print();
  std::vector<Production> get_productions_from(int type);
};

#endif