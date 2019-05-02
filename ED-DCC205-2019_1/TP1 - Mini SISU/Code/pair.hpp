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

  bool operator>=(Pair other) const{
    if(this->first == other.first){
      return this->second >= other.second;
    }else{
      return this->first >= other.first;
    }
  }
};

#endif
