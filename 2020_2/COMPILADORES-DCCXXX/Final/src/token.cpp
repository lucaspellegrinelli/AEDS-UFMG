#include "token.h"

#include "const.h"
#include <iostream>

Token::Token(std::string value, int type){
  this->value = value;
  this->type = type;
}

Token::Token(char value, int type){
  this->value = std::string(1, value);
  this->type = type;
}

void Token::print(){
  std::cout << "Token: [" << this->value << "\t " << token_type_to_str(this->type) << "] " << std::endl;
}