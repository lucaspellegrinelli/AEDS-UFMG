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
  std::cout << (this->raiz == nullptr) << std::endl;
  if(this->raiz != nullptr){
    return this->raiz->pre_ordem();
  }else{
    ListaEncadeada l;
    return l;
  }
}

ListaEncadeada BST::em_ordem(){
  if(this->raiz != nullptr){
    return this->raiz->em_ordem();
  }else{
    ListaEncadeada l;
    return l;
  }
}

ListaEncadeada BST::pos_ordem(){
  if(this->raiz != nullptr){
    return this->raiz->pos_ordem();
  }else{
    ListaEncadeada l;
    return l;
  }
}
