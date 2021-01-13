#include <cstddef>
#include <iostream>
#include "listaencadeada.h"

ListaEncadeada::ListaEncadeada(){
  this->primeiro = nullptr;
  this->ultimo = nullptr;
}

ListaEncadeada::~ListaEncadeada(){
  node_t *nodeAntes = nullptr;
  node_t *nodeDepois = this->primeiro;

  while (nodeDepois != nullptr) {
    nodeAntes = nodeDepois;
    nodeDepois = nodeDepois->proximo;
    delete nodeAntes;
  }
}

void ListaEncadeada::insere_elemento(int elem){
  node_t *newNode = new node_t();
  newNode->elemento = elem;
  newNode->proximo = nullptr;

  if(this->primeiro == nullptr){
    this->primeiro = newNode;
    this->ultimo = newNode;
  } else{
    newNode->anterior = this->ultimo;
    this->ultimo->proximo = newNode;
    this->ultimo = newNode;
  }
}

void ListaEncadeada::insere_primeiro(int elem){
  node_t *newNode = new node_t();
  newNode->elemento = elem;
  if(this->primeiro != nullptr) newNode->proximo = this->primeiro;
  newNode->anterior = nullptr;
  this->primeiro->anterior = newNode;
  this->primeiro = newNode;
}

int ListaEncadeada::get_iesimo(int pos){
  node_t *nodeAtual = this->primeiro;
  int cont = 0;
  while(nodeAtual != nullptr && cont++ < pos) nodeAtual = nodeAtual->proximo;

  if(cont - 1 != pos) return 0;
  else return nodeAtual->elemento;
}

void ListaEncadeada::remover_elemento(){
  this->ultimo = this->ultimo->anterior;
  delete this->ultimo->proximo;
  this->ultimo->proximo = nullptr;
}

void ListaEncadeada::remover_primeiro(){
  this->primeiro = this->primeiro->proximo;
  delete this->primeiro->anterior;
  this->primeiro->anterior = nullptr;
}

void ListaEncadeada::inserir_iesimo(int elem, int pos){
  int cont = 0;
  node_t *nodeAtual = this->primeiro;

  node_t *newNode = new node_t();
  newNode->elemento = elem;

  if(nodeAtual == nullptr){
    newNode->proximo = nullptr;
    newNode->anterior = nullptr;
    this->primeiro = newNode;
    this->ultimo = newNode;
  }else{
    while(nodeAtual != nullptr && cont++ < pos - 1) nodeAtual = nodeAtual->proximo;

    newNode->proximo = nodeAtual->proximo;
    newNode->anterior = nodeAtual;
    nodeAtual->proximo = newNode;

    if(newNode->proximo == nullptr)
      this->ultimo = newNode;
  }
}

void ListaEncadeada::remover_iesimo(int pos){
  int cont = 0;
  node_t *nodeAtual = this->primeiro;

  if(nodeAtual == nullptr){
    return;
  }else{
    while(nodeAtual != nullptr && cont++ < pos) nodeAtual = nodeAtual->proximo;

    if(cont - 1 != pos) return;

    if(pos == 0){
      this->primeiro = nullptr;
      delete this->primeiro;
    }

    if(nodeAtual->proximo == nullptr){
      this->ultimo = nullptr;
      delete this->ultimo;
    }

    if(nodeAtual->anterior != nullptr) nodeAtual->anterior->proximo = nodeAtual->proximo;
    if(nodeAtual->proximo  != nullptr) nodeAtual->proximo->anterior = nodeAtual->anterior;
    nodeAtual = nullptr;

    delete nodeAtual;
  }
}

int ListaEncadeada::tamanho(){
  int tamanho = 0;
  node_t *nodeAtual = this->primeiro;

  for(tamanho = 0; nodeAtual != nullptr; tamanho++){
    nodeAtual = nodeAtual->proximo;
  }

  return tamanho;
}

bool ListaEncadeada::checa_palindromo(){
  int size = tamanho();
  for(int i = 0; i < (size / 2); i++){
    if(get_iesimo(i) != get_iesimo(size - i - 1)) return false;
  }

  return true;
}
