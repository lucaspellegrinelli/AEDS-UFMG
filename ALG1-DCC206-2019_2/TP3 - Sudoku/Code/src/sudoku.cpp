#include "sudoku.h"

int Sudoku::branch_count = 0;

Sudoku::Sudoku(){ }

Sudoku::Sudoku(int N, int I, int J){
  this->N = N;
  this->I = I;
  this->J = J;

  known_nodes = new int[N * N];
  node_values = new int[N * N];
  node_adjs_size = new int[N * N];
  min_can_be = new int[N * N];
  how_many_can_be = new int[N * N];
  node_adjs = new int*[N * N];
  can_be = new bool*[N * N];
  
  for(int i = 0; i < N * N; i++){
    node_adjs[i] = new int[N * N];
    can_be[i] = new bool[N];
  }
}

bool Sudoku::solve(){
  this->create_initial_edges();

  // Aumenta incrementalmente a profundidade da busca de respostas
  // até que o limite de linhas alternativas testadas seja alcançada
  for(int depth = 0; branch_count <= MAX_BRANCH_COUNT; depth++){
    Sudoku *copy = this->copy();
    
    // Caso ache a resposta, faça essa instância ser a resposta e retorne
    if(copy->solve_depth(depth)){
      this->replace_with(copy);
      return true;
    }
  }

  this->solve_depth(0);
  return false;
}

bool Sudoku::solve_depth(int depth){
  // Repita enquanto exista algum nó não definido
  int known_node_i = 0;
  while(known_nodes_count < N * N){
    // Passe pelos novos valores da lista de nós que eu já conheço o valor
    for(; known_node_i < known_nodes_count; known_node_i++){
      int node = known_nodes[known_node_i];
      int node_value = node_values[node];

      // Para cada um dos nós em sua lista de adjacência...
      for(int adj_i = 0; adj_i < node_adjs_size[node]; adj_i++){
        int adj_node = node_adjs[node][adj_i];

        // Proiba que cada um deles tenha o mesmo valor do nó que eu já
        // sei o valor
        if(can_be[adj_node][node_value - 1]){
          how_many_can_be[adj_node]--;
          can_be[adj_node][node_value - 1] = false;

          // Se o que for restringido bater com o menor possível, ache o próximo
          // menor
          if(node_value == min_can_be[adj_node]){
            min_can_be[adj_node] = -1;
            for(int i = 0; i < N; i++){
              if(can_be[adj_node][i]){
                min_can_be[adj_node] = i + 1;
                break;
              }
            }
          }
        }

        // Se só existe uma opção restante para um nó e ele não tem um valor
        // definido ainda, defina-o para o último valor restante
        if(node_values[adj_node] == 0 && how_many_can_be[adj_node] == 1){
          node_values[adj_node] = min_can_be[adj_node];
          known_nodes[known_nodes_count++] = adj_node;
        }
      }
    }

    if(depth == 0 || branch_count > MAX_BRANCH_COUNT){
      // Passe por cada um dos nós...
      for(int node = 0; node < N * N; node++){
        // Se ele ainda não foi definido e existe alguma opção de número que
        // ele não está restrito, defina-o para o menor número possível
        if(node_values[node] == 0 && how_many_can_be[node] > 0){
          node_values[node] = min_can_be[node];
          known_nodes[known_nodes_count++] = node;
          break;
        }
      }
    }else{
      // Encontra o nó com o menor número de possibilidades de número
      int min_options_node = -1;
      int min_options_count = 9;
      for(int node = 0; node < N * N; node++){
        if(node_values[node] == 0 && how_many_can_be[node] > 0){
          if(how_many_can_be[node] < min_options_count){
            min_options_node = node;
            min_options_count = how_many_can_be[node];
          }
        }
      }

      if(min_options_node == -1) return false;
      
      // Para cada uma das possibilidades dele, checa se conseguimos resolver
      // o Sudoku
      for(int i = 0; i < N && branch_count <= MAX_BRANCH_COUNT; i++){
        if(can_be[min_options_node][i]){
          branch_count++;
          Sudoku *copy = this->copy();
          copy->set_edge_value(min_options_node, i + 1);

          if(copy->solve_depth(depth - 1)){
            this->replace_with(copy);
            return true;
          }
        }
      }

      return false;
    }
  }

  // Checa se todos os nós tem um valor que eles poderiam ter
  bool answer_correct = true;
  for(int i = 0; i < N * N; i++){
    if(!can_be[i][node_values[i] - 1] || node_values[i] == 0){
      answer_correct = false;
      break;
    }
  }

  return answer_correct;
}

// Seta o valor de um quadrado
void Sudoku::set_edge_value(int edge, int value){
  node_values[edge] = value;
  min_can_be[edge] = value;
  for(int i = 0; i < N; i++){
    can_be[edge][i] = i == (value - 1);
  }
  known_nodes[known_nodes_count++] = edge;
}

// Copia os dados dessa instância para outra
Sudoku * Sudoku::copy(){
  Sudoku *copy = new Sudoku(N, I, J);
  
  copy->known_nodes_count = known_nodes_count;
  for(int i = 0; i < N * N; i++){
    copy->known_nodes[i] = known_nodes[i];
    copy->node_values[i] = node_values[i];
    copy->node_adjs_size[i] = node_adjs_size[i];
    copy->min_can_be[i] = min_can_be[i];
    copy->how_many_can_be[i] = how_many_can_be[i];
    
    for(int j = 0; j < N; j++){
      copy->can_be[i][j] = can_be[i][j];
    }

    for(int j = 0; j < N * N; j++){
      copy->node_adjs[i][j] = node_adjs[i][j];
    }
  }

  return copy;
}

// Copia os dados de uma outra instância para essa
void Sudoku::replace_with(Sudoku *other){
  N = other->N;
  I = other->I;
  J = other->J;

  known_nodes_count = other->known_nodes_count;
  for(int i = 0; i < N * N; i++){
    known_nodes[i] = other->known_nodes[i];
    node_values[i] = other->node_values[i];
    node_adjs_size[i] = other->node_adjs_size[i];
    min_can_be[i] = other->min_can_be[i];
    how_many_can_be[i] = other->how_many_can_be[i];
    
    for(int j = 0; j < N; j++){
      can_be[i][j] = other->can_be[i][j];
    }

    for(int j = 0; j < N * N; j++){
      node_adjs[i][j] = other->node_adjs[i][j];
    }
  }
}

void Sudoku::create_initial_edges(){
  this->create_block_edges();
  this->create_line_col_edges();
}

 void Sudoku::create_block_edges(){
    // Define a coluna inicial de cada bloco
  for(int block_x = 0; block_x < N; block_x += I){
    int next_block_x = block_x + I;

    // Define a linha inicial de cada bloco
    for(int block_y = 0; block_y < N; block_y += J){
      int next_block_y = block_y + J;

      // Armazena todos os nós daquele bloco
      int block_nodes[I * J];
      int block_node_count = 0;
      for(int i = block_x; i < next_block_x; i++){
        for(int j = block_y; j < next_block_y; j++){
          block_nodes[block_node_count++] = i * N + j;
        }
      }

      // Para cada nó, adicione todos os outros do mesmo bloco em sua lista
      // de adjacência
      for(int dest_node : block_nodes){
        for(int new_adj : block_nodes){
          if(dest_node == new_adj) continue;
          node_adjs[dest_node][node_adjs_size[dest_node]++] = new_adj;
        }
      }
    }
  }
}

void Sudoku::create_line_col_edges(){
  // Para cada uma das linhas/colunas
  for(int i = 0; i < N; i++){
    int line_nodes[N];
    int line_node_count = 0;
    int col_nodes[N];
    int col_node_count = 0;

    // Guarda todos os nós na coluna/linha atual
    for(int j = 0; j < N; j++){
      line_nodes[line_node_count++] = i * N + j;
      col_nodes[col_node_count++] = j * N + i;
    }

    // Para cada nó, adicione todos os outros da mesma linha e coluna em sua
    // lista de adjacência
    for(int j = 0; j < N; j++){
      for(int k = 0; k < N; k++){
        int line_dest_node = line_nodes[j];
        int line_new_adj = line_nodes[k];
        int col_dest_node = col_nodes[j];
        int col_new_adj = col_nodes[k];

        if(line_dest_node != line_new_adj){
          // Pega a última posição da lista de adjacencias do nó atual
          int last_adj_list_pos = node_adjs_size[line_dest_node];

          // Coloca o novo nó nessa posição
          node_adjs[line_dest_node][last_adj_list_pos] = line_new_adj;

          // Avança o marcador de última posição
          node_adjs_size[line_dest_node]++;
        }

        if(col_dest_node != col_new_adj){
          // Pega a última posição da lista de adjacencias do nó atual
          int last_adj_list_pos = node_adjs_size[col_dest_node];

          // Coloca o novo nó nessa posição
          node_adjs[col_dest_node][last_adj_list_pos] = col_new_adj;

          // Avança o marcador de última posição
          node_adjs_size[col_dest_node]++;
        }
      }
    }
  }
}

Sudoku::~Sudoku(){
  for(int i = 0; i < N * N; i++){
    delete[] this->node_adjs[i];
    delete[] this->can_be[i];
  }

  delete[] this->known_nodes;
  delete[] this->node_values;
  delete[] this->node_adjs;
  delete[] this->node_adjs_size;
  delete[] this->can_be;
  delete[] this->how_many_can_be;
  delete[] this->min_can_be;
}