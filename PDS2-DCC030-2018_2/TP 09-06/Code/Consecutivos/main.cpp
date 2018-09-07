#include<iostream>
#include "listaencadeada.h"

void CHECK(int a){
  std::cout << a << std::endl;
}

int main(){
  ListaEncadeada lista; //chamando lista via construtor vazio
  lista.insere_elemento(1);
  lista.insere_elemento(1);
  lista.insere_elemento(2);
  lista.insere_elemento(1);
  lista.insere_elemento(2);
  lista.insere_elemento(2);
  lista.insere_elemento(3);
  lista.insere_elemento(1);
  lista.insere_elemento(3);
  lista.insere_elemento(3);
  lista.insere_elemento(3);
  lista.insere_elemento(2);

  lista.remove_consecutivos();

  int element1 = lista.get_iesimo(0);
  int element2 = lista.get_iesimo(1);
  int element3 = lista.get_iesimo(2);
  int element4 = lista.get_iesimo(3);
  int element5 = lista.get_iesimo(4);
  int element6 = lista.get_iesimo(5);
  int element7 = lista.get_iesimo(6);
  int element8 = lista.get_iesimo(7);

  CHECK(element1 == 1);
  CHECK(element2 == 2);
  CHECK(element3 == 1);
  CHECK(element4 == 2);
  CHECK(element5 == 3);
  CHECK(element6 == 1);
  CHECK(element7 == 3);
  CHECK(element8 == 2);
}
