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

ListaEncadeada Node::pre_ordem(){
  ListaEncadeada l;

  l.insere_elemento(this->valor);

  if(esquerda != nullptr){
    ListaEncadeada listEsq = esquerda->pre_ordem();
    for(int i = 0; i < listEsq.tamanho(); i++){
      l.insere_elemento(listEsq.get_iesimo(i));
    }
  }

  if(direita != nullptr){
    ListaEncadeada listDir = direita->pre_ordem();
    for(int i = 0; i < listDir.tamanho(); i++){
      l.insere_elemento(listDir.get_iesimo(i));
    }
  }

  return l;
}

ListaEncadeada Node::em_ordem(){
  ListaEncadeada l;

  if(esquerda != nullptr){
    ListaEncadeada listEsq = esquerda->em_ordem();
    for(int i = 0; i < listEsq.tamanho(); i++){
      l.insere_elemento(listEsq.get_iesimo(i));
    }
  }

  l.insere_elemento(this->valor);

  if(direita != nullptr){
    ListaEncadeada listDir = direita->em_ordem();
    for(int i = 0; i < listDir.tamanho(); i++){
      l.insere_elemento(listDir.get_iesimo(i));
    }
  }

  return l;
}

ListaEncadeada Node::pos_ordem(){
  ListaEncadeada l;

  if(esquerda != nullptr){
    ListaEncadeada listEsq = esquerda->pos_ordem();
    for(int i = 0; i < listEsq.tamanho(); i++){
      l.insere_elemento(listEsq.get_iesimo(i));
    }
  }

  if(direita != nullptr){
    ListaEncadeada listDir = direita->pos_ordem();
    for(int i = 0; i < listDir.tamanho(); i++){
      l.insere_elemento(listDir.get_iesimo(i));
    }
  }

  l.insere_elemento(this->valor);

  return l;
}
