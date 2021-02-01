#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <vector>

class Production{
public:
    int index;
    int left;
    std::vector<int> right;

    int marker;

    Production(){ }
    Production(int left, std::vector<int> right);

    void set_index(int index);
    void print();
    void print_with_marker();
};

#endif