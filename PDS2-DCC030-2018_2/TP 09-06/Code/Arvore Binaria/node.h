#ifndef PDS2_NODE_H
#define PDS2_NODE_H

#include "listaencadeada.h"

class Node {
private:
  Node *esquerda;
  Node *direita;
  int valor;

public:
  Node(int valor);
  ~Node();
  void inserir_elemento(int elemento);
  bool existe_element(int elemento);
  ListaEncadeada pre_order();
  ListaEncadeada em_ordem();
  ListaEncadeada pos_ordem();
};

#endif
