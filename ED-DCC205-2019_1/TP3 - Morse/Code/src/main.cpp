#include <iostream>
#include <fstream>
#include <sstream>

#include "tree.hpp"

int main(int argc, char *argv[]){
  std::ifstream config_file;
  config_file.open("src/morse.txt");

  if(!config_file){
    std::cout << "Não foi possível abrir o arquivo de configuração. Confira que o arquivo está na pasta src/ com o nome 'morse.txt'" << std::endl;
    exit(1);
  }

  Tree t;

  std::string full_config;
  std::string key;
  std::string value;

  while(config_file >> value >> key){
    t.insert(key, value);
  }

  std::string line;
  while(std::getline(std::cin, line)){
    std::istringstream line_stream(line);

    std::string code;
    while(line_stream >> code){
      std::cout << (code == "/" ? " " : t.search(code));
    }

    std::cout << std::endl;
  }

  if(argc >= 2){
    t.pre_order();
  }
}
