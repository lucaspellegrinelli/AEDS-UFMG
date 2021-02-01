#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token{
public:
  std::string value;
  int type;

  Token(){ }
  Token(std::string value, int type);
  Token(char value, int type);

  void print();
};

#endif