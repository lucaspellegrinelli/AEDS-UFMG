#include "BST.h"

BST::BST(){
  this->raiz = nullptr;
  this->num_elementos_inseridos = 0;
}

BST::~BST(){
  delete this->raiz;
}

void BST::inserir_elemento(int elemento){
  if(this->num_elementos_inseridos == 0)
    this->raiz = new Node(elemento);
  else if(!this->raiz->existe_elemento(elemento))
    this->raiz->inserir_elemento(elemento);

  this->num_elementos_inseridos++;
}

bool BST::existe_elemento(int elemento){
  return this->raiz->existe_elemento(elemento);
}

ListaEncadeada BST::pre_ordem(){
  return this->raiz->pre_ordem();
}

ListaEncadeada BST::em_ordem(){
  return this->raiz->em_ordem();
}

ListaEncadeada BST::pos_ordem(){
  return this->raiz->pos_ordem();
}
