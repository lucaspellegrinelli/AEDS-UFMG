#include "BST.h"

BST::BST(){

}

BST::~BST(){
  delete this->raiz;
}

void BST::inserir_elemento(int elemento){
  if(this->num_elementos_inseridos == 0)
    this->raiz = new Node(elemento);
  else
    this->raiz->inserir_elemento(elemento);

  this->num_elementos_inseridos++;
}

bool BST::existe_element(int elemento){
  return this->raiz->existe_element(elemento);
}

ListaEncadeada BST::pre_ordem(){
  ListaEncadeada l;
  return l;
}

ListaEncadeada BST::em_ordem(){
  ListaEncadeada l;
  return l;
}

ListaEncadeada BST::pos_ordem(){
  ListaEncadeada l;
  return l;
}
