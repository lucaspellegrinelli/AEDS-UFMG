#include<iostream>
#include "listaencadeada.h"

void CHECK(int a){
  std::cout << a << std::endl;
}

int main(){
  ListaEncadeada lista; //chamando lista via construtor vazio
  lista.insere_elemento(4);
  lista.insere_elemento(7);
  lista.insere_elemento(3);
  lista.insere_elemento(9);
  lista.insere_elemento(6);
  lista.insere_elemento(8);
  lista.insere_elemento(5);
  lista.insere_elemento(1);

  int element1 = lista.k_esimo(true, 0);
  int element2 = lista.k_esimo(true, 1);
  int element3 = lista.k_esimo(true, 2);
  int element4 = lista.k_esimo(true, 3);
  int element5 = lista.k_esimo(false, 0);
  int element6 = lista.k_esimo(false, 1);
  int element7 = lista.k_esimo(false, 2);
  int element8 = lista.k_esimo(false, 3);

  CHECK(element1 == 4);
  CHECK(element2 == 7);
  CHECK(element3 == 3);
  CHECK(element4 == 9);
  CHECK(element5 == 1);
  CHECK(element6 == 5);
  CHECK(element7 == 8);
  CHECK(element8 == 6);
}
