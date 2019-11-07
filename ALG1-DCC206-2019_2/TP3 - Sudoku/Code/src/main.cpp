#include <iostream>
#include <fstream>
#include <algorithm>

// Falha nos testes:
// 883.txt, 885.txt, 991.txt e 994.txt

int main(int argc, char *argv[]){
  if(argc < 2) return 0;

  std::ifstream infile;
  infile.open(argv[1]);

  int N, I, J;
  infile >> N >> J >> I;

  int known_nodes[N * N]; // Lista de nós que já sei quanto valem
  int known_nodes_count = 0; // Tamanho da lista de nós já descobertos

  int node_values[N * N]; // Valor de cada nó
  int node_adjs[N * N][N * N]; // Lista de adjacência de cada nó
  int node_adjs_size[N * N]; // Tamanho da lista de adjacência de cada nó

  bool can_be[N * N][N]; // Indica quais números cada nó pode ser
  int how_many_can_be[N * N]; // Número de opções ainda abertas
  int min_can_be[N * N]; // Menor valor possível para aquele nó

  for(int i = 0; i < N * N; i++){
    int value;
    infile >> value;

    // Coloca o valor lido no vetor de valores por nó
    node_values[i] = value;

    // Se o valor for diferente de 0, adicione-o na lista de nós com valor conhecido
    if(value == 0){
      how_many_can_be[i] = N;
      min_can_be[i] = 1;
    }else{
      known_nodes[known_nodes_count++] = i;
      how_many_can_be[i] = 1;
      min_can_be[i] = value;
    }

    // Inicializa o valor do número de nós adjacentes para 0
    node_adjs_size[i] = 0;

    // Iniciliza a lista de números que o nó pode ser
    for(int j = 0; j < N; j++){
      can_be[i][j] = value == 0 ? true : j == value - 1;
    }
  }

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

        // Restrinja que cada um deles tenha o mesmo valor do nó que eu já
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

    // Passe por cada um dos nós não definidos...
    for(int node = 0; node < N * N; node++){
      // Se existe alguma opção de número que ele não está restrito,
      // defina-o para o menor número possível
      if(node_values[node] == 0 && how_many_can_be[node] > 0){
        node_values[node] = min_can_be[node];
        known_nodes[known_nodes_count++] = node;
        break;
      }
    }
  }

  // Checa se todos os nós tem um valor que eles poderiam ter
  bool answer_correct = true;
  for(int i = 0; i < N * N; i++){
    if(!can_be[i][node_values[i] - 1]){
      answer_correct = false;
      break;
    }
  }

  if(answer_correct){
    std::cout << "solução" << std::endl;
  }else{
    std::cout << "sem solução" << std::endl;
  }

  // Imprime a solução na tela
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      int index = i * N + j;
      std::cout << node_values[index] << " ";
    }
    std::cout << std::endl;
  }
}
