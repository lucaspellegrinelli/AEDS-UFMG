#include <iostream>
#include <fstream>
#include <algorithm>

#include "sudoku.h"

int main(int argc, char *argv[]){
  if(argc < 2) return 0;

  std::ifstream infile;
  infile.open(argv[1]);

  int N, I, J;
  infile >> N >> J >> I;

  Sudoku *sudoku = new Sudoku(N, I, J);

  for(int i = 0; i < N * N; i++){
    int value;
    infile >> value;

    // Coloca o valor lido no vetor de valores por nó
    sudoku->node_values[i] = value;

    // Se o valor for diferente de 0, adicione-o na lista de nós com valor conhecido
    if(value == 0){
      sudoku->how_many_can_be[i] = N;
      sudoku->min_can_be[i] = 1;
    }else{
      sudoku->known_nodes[sudoku->known_nodes_count++] = i;
      sudoku->how_many_can_be[i] = 1;
      sudoku->min_can_be[i] = value;
    }

    // Inicializa o valor do número de nós adjacentes para 0
    sudoku->node_adjs_size[i] = 0;

    // Iniciliza a lista de números que o nó pode ser
    for(int j = 0; j < N; j++){
      sudoku->can_be[i][j] = value == 0 ? true : j == value - 1;
    }
  }

  // Solves the board
  bool answer_correct = sudoku->solve();

  if(answer_correct){
    std::cout << "solução" << std::endl;
  }else{
    std::cout << "sem solução" << std::endl;
  }

  // Imprime a solução na tela
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      int index = i * N + j;
      std::cout << sudoku->node_values[index] << " ";
    }
    std::cout << std::endl;
  }

  delete sudoku;
}
