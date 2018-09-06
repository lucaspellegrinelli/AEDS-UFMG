#include<iostream>
#include "listaencadeada.h"

int main(){
  ListaEncadeada l;

  l.insere_elemento(5);
  l.insere_elemento(7);
  l.insere_elemento(9);

  l.inserir_iesimo(3, 1);

  l.insere_primeiro(1);

  l.remover_elemento();

  l.remover_primeiro();

  l.remover_iesimo(1);

   std::cout << l.tamanho() << std::endl;

   for(int i = 0; i < l.tamanho(); i++){
     std::cout << i << ": " << l.get_iesimo(i) << std::endl;
   }
}
