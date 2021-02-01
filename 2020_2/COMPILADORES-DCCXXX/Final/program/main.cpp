#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "lexico.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "Informe um arquivo para ser processado" << std::endl;
  }

  std::vector<Token> all_tokens;

  //Obtém tokens do analisador léxico
  analisador_lexico(all_tokens, argv[1]);

  for(Token t : all_tokens){
    t.print();
  }
}