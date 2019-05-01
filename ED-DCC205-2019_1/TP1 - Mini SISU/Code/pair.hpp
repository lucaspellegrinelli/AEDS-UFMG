#ifndef PAIR_H
#define PAIR_H

template <class T, class U>
class Pair{
public:
  T first;
  U second;

  Pair(){ }

  Pair(T first, U second){
    this->first = first;
    this->second = second;
  }
};

#endif
