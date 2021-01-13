#ifndef TREE
#define TREE

#include <string>
#include <iostream>

/*
  Classe responsável por armazenar as informações de cada nó da árvore.
   - std::string key: Armazena o código desse nó
   - std::string value: Armazena qual a letra correspondente ao código desse nó

   - Node *point: Ponteiro para o nó filho que representa o código desse nó
                  seguido por um ponto.
    - Node *line: Ponteiro para o nó filho que representa o código desse nó
                   seguido por uma linha.
*/
class Node{
public:
  std::string key;
  std::string value;
  Node *point;
  Node *line;

  // Construtor vazio
  Node(){
    this->key = "";
    this->value = "";
    this->point = nullptr;
    this->line = nullptr;
  }

  // Método de escrita da árvore em pré-ordem na saída padrão.
  void pre_order(){
    if(this->key != ""){
      std::cout << this->value << " " << this->key << std::endl;
    }

    if(this->point) this->point->pre_order();
    if(this->line) this->line->pre_order();
  }

  // Destrutor da classe, deleta os dois ponteiros criados
  ~Node(){
    delete this->point;
    delete this->line;
  }
};

/*
  Classe responsável por administrar as funções básicas da árvore trie que será
  usada para armazenar os códigos morse.

  - Node *root: Nó raíz da árvore. Não armazena nenhuma informação, apenas
                ponteiros para os nós que contém apenas um ponto ou uma linha.
*/
class Tree{
public:
  Node *root;

  // Construtor vazio
  Tree(){
    this->root = new Node();
  }

  /*
    Método responsável por adicionar mais um nó na árvore, com uma chave e um
    valor específico, caso essa chave ainda não exista na árvore.
    Isso é feito fazendo uma pesquisa na árvore até que se encontre o nó
    cuja chave seja igual à chave do item a ser inserido. Assim é simplesmente
    necessário modificar o valor guardado por esse nó para o novo valor.

    ENTRADA
     - std::string key: Chave do novo valor
     - std::string value: Novo valor

    SAIDA
     - void
  */
  void insert(std::string key, std::string value){
    Node *curr_node = root;

    for(unsigned int i = 0; i < key.size(); i++){
      if(key[i] == '.'){
        // Caso ainda não exista um caminho que adicione um ponto no código
        // atual, crie um nó para esse caminho.
        if(!curr_node->point) curr_node->point = new Node();
        curr_node = curr_node->point;
      }else if(key[i] == '-'){
        // Caso ainda não exista um caminho que adicione uma linha no código
        // atual, crie um nó para esse caminho.
        if(!curr_node->line) curr_node->line = new Node();
        curr_node = curr_node->line;
      }
    }

    curr_node->key = key;
    curr_node->value = value;
  }

  /*
    Método responsável por encontrar qual o valor correspondente à uma chave
    específica. Isso é feito passando por cada nó, e dependendo do código,
    escolhendo o caminho que adiciona um ponto ao código atual ou uma linha
    ao código atual, até chegar no código desejado e assim retornando o valor
    desse nó.

    ENTRADA
     - std::string key: Chave do valor que se deseja encontrar

    SAIDA:
     - std::string: Valor cuja chave é igual à chave recebida como parâmetro. Caso
                    a chave não exista na árvore, uma string vazia é retornada.
  */
  std::string search(std::string key){
    Node *curr_node = root;

    for(unsigned int i = 0; i < key.size(); i++){
      if(key[i] == '.'){
        if(!curr_node->point) return "";
        curr_node = curr_node->point;
      }else if(key[i] == '-'){
        if(!curr_node->line) return "";
        curr_node = curr_node->line;
      }
    }

    return curr_node->value;
  }

  // Método que chama a função de impressão de pré-ordem no nó raíz da árvore.
  void pre_order(){
    if(this->root) this->root->pre_order();
  }

  // Destrutor deletando o ponteiro para a raíz da árvore
  ~Tree(){
    delete root;
  }
};

#endif
