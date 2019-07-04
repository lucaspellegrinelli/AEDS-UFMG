#include <iostream>
#include <fstream>
#include <sstream>

#include "tree.hpp"

int main(int argc, char *argv[]){
  // Abre o arquivo com as definições do alfebeto morse
  std::ifstream config_file;
  config_file.open("src/morse.txt");

  // Mensagem de erro caso o arquivo não consiga ser aberto
  if(!config_file){
    std::cout << "Não foi possível abrir o arquivo de configuração. Confira que o arquivo está na pasta src/ com o nome 'morse.txt'" << std::endl;
    exit(1);
  }

  // Inicialização da árvore
  Tree t;

  std::string full_config;
  std::string key;
  std::string value;

  // Leitura das linhas do arquivo de definição do morse adicionando cada
  // item na árvore
  while(config_file >> value >> key){
    t.insert(key, value);
  }

  std::string line;
  // Leitura para cada linha do input padrão
  while(std::getline(std::cin, line)){
    std::istringstream line_stream(line);

    std::string code;
    // Para cada bloco em morse, traduza para alfabeto alfanumérico e escreva
    // na saída padrão
    while(line_stream >> code){
      std::cout << (code == "/" ? " " : t.search(code));
    }

    std::cout << std::endl;
  }

  // Caso o argumento de escrita da árvore esteja presente, chame o método que
  // imprime a árvore em pré ordem
  if(argc >= 2){
    t.pre_order();
  }
}
