#include "node.h"
#include "listaencadeada.h"
#include <iostream>

void CHECK(int a){
  std::cout << a << std::endl;
}

int main(){
  Node no = Node(4);
no.inserir_elemento(2);
no.inserir_elemento(5);
no.inserir_elemento(6);
no.inserir_elemento(0);
no.inserir_elemento(3);

ListaEncadeada L=no.pre_ordem();
CHECK(L.get_iesimo(0)==4);
CHECK(L.get_iesimo(1)==2);
CHECK(L.get_iesimo(2)==0);
CHECK(L.get_iesimo(3)==3);
CHECK(L.get_iesimo(4)==5);
CHECK(L.get_iesimo(5)==6);

ListaEncadeada a=no.em_ordem();
  for(int i = 0; i < 6  ; i++)
    std::cout << a.get_iesimo(i) << " == " << i << std::endl;

L=no.pos_ordem();
CHECK(L.get_iesimo(0)==0);
CHECK(L.get_iesimo(1)==3);
CHECK(L.get_iesimo(2)==2);
CHECK(L.get_iesimo(3)==6);
CHECK(L.get_iesimo(4)==5);
CHECK(L.get_iesimo(5)==4);
}
