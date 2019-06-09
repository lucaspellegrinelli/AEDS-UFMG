#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "sort_request.hpp"

int main(int argc, char *argv[]){
  // Inicializa a seed dos métodos que utilizem o método "rand()" para o tempo
  // atual (o que evita que o "rand()" gere sempre os mesmos números)
  srand (time(NULL));

  // Inicializa e executa o "SortRequest" com os parâmetros recebidos
  // via linha de comando
  SortRequest sr = SortRequest(argv[1], argv[2], argv[3], argc > 4);
  sr.run();

  return 0;
}
