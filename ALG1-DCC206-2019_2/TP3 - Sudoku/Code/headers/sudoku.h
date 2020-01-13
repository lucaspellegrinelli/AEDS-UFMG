#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>

#define MAX_BRANCH_COUNT 1000

class Sudoku{
public:
  int *known_nodes; // Lista de nós que já sei quanto valem
  int known_nodes_count = 0; // Tamanho da lista de nós já descobertos

  int *node_values; // Valor de cada nó
  int **node_adjs; // Lista de adjacência de cada nó
  int *node_adjs_size; // Tamanho da lista de adjacência de cada nó

  bool **can_be; // Indica quais números cada nó pode ser
  int *how_many_can_be; // Número de opções ainda abertas
  int *min_can_be; // Menor valor possível para aquele nó

  static int branch_count;

  int N;
  int I;
  int J;

  Sudoku();
  Sudoku(int N, int I, int J);
  ~Sudoku();

  void set_edge_value(int edge, int value);

  bool solve();

  Sudoku * copy();
  void replace_with(Sudoku *other);

  void create_initial_edges();

protected:
  bool solve_depth(int depth);

  void create_block_edges();
  void create_line_col_edges();
};

#endif
