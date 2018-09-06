#include "node.h"

Node::Node(int valor){
  this->valor = valor;
  this->direita = nullptr;
  this->esquerda = nullptr;
}

Node::~Node(){
  delete this->direita;
  delete this->esquerda;
}

void Node::inserir_elemento(int elemento){
  if(elemento > valor){
    if(direita == nullptr) direita = new Node(elemento);
    else direita->inserir_elemento(elemento);
  }else if(elemento < valor){
    if(esquerda == nullptr) esquerda = new Node(elemento);
    else esquerda->inserir_elemento(elemento);
  }
}

bool Node::existe_element(int elemento){
  if(elemento == valor)
    return true;
  else if(elemento < valor && esquerda != nullptr)
    return esquerda->existe_element(elemento);
  else if(direita != nullptr)
    return direita->existe_element(elemento);
  else return false;
}

ListaEncadeada Node::pre_order(){
  ListaEncadeada l;
}

ListaEncadeada Node::em_ordem(){
  ListaEncadeada l;
  return l;
}

ListaEncadeada Node::pos_ordem(){
  ListaEncadeada l;
  return l;
}
