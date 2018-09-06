#include<iostream>
#include "listaencadeada.h"

int main(){
  ListaEncadeada lista;     // chamando lista via construtor vazio
  lista.insere_elemento(4);
  lista.insere_elemento(5);
  lista.insere_elemento(3);
  lista.remover_iesimo(2);
  lista.remover_iesimo(1);
  lista.remover_iesimo(0);

  std::cout << (lista.tamanho()) << std::endl;
}
