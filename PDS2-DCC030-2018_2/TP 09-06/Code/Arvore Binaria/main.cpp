#include "node.h"
#include "listaencadeada.h"
#include "BST.h"
#include <iostream>

void CHECK(int a){
  if(a == 0)
    std::cerr << "Erro" << std::endl;
  else
    std::cout << "Correto" << std::endl;
}

void test3(){
  Node no = Node(3);
  no.inserir_elemento(4);
  no.inserir_elemento(6);
  no.inserir_elemento(5);
  no.inserir_elemento(1);

  CHECK(no.existe_elemento(3)==1);
  CHECK(no.existe_elemento(4)==1);
  CHECK(no.existe_elemento(1)==1);
  CHECK(no.existe_elemento(5)==1);
  CHECK(no.existe_elemento(6)==1);
  CHECK(no.existe_elemento(2)==0);
}

void test4(){
  BST arvore = BST();
  arvore.inserir_elemento(6);
  arvore.inserir_elemento(5);
  arvore.inserir_elemento(3);
  arvore.inserir_elemento(4);
  arvore.inserir_elemento(1);

  CHECK(arvore.existe_elemento(3)==1);
  CHECK(arvore.existe_elemento(4)==1);
  CHECK(arvore.existe_elemento(1)==1);
  CHECK(arvore.existe_elemento(5)==1);
  CHECK(arvore.existe_elemento(6)==1);
  CHECK(arvore.existe_elemento(2)==0);
}

void test5(){
  Node no = Node(4);
  no.inserir_elemento(2);
  no.inserir_elemento(5);
  no.inserir_elemento(6);
  no.inserir_elemento(0);
  no.inserir_elemento(3);

  ListaEncadeada L_pre=no.pre_ordem();
  CHECK(L_pre.get_iesimo(0)==4);
  CHECK(L_pre.get_iesimo(1)==2);
  CHECK(L_pre.get_iesimo(2)==0);
  CHECK(L_pre.get_iesimo(3)==3);
  CHECK(L_pre.get_iesimo(4)==5);
  CHECK(L_pre.get_iesimo(5)==6);

  ListaEncadeada L_em=no.em_ordem();
  CHECK(L_em.get_iesimo(0)==0);
  CHECK(L_em.get_iesimo(1)==2);
  CHECK(L_em.get_iesimo(2)==3);
  CHECK(L_em.get_iesimo(3)==4);
  CHECK(L_em.get_iesimo(4)==5);
  CHECK(L_em.get_iesimo(5)==6);

  ListaEncadeada L_pos=no.pos_ordem();
  CHECK(L_pos.get_iesimo(0)==0);
  CHECK(L_pos.get_iesimo(1)==3);
  CHECK(L_pos.get_iesimo(2)==2);
  CHECK(L_pos.get_iesimo(3)==6);
  CHECK(L_pos.get_iesimo(4)==5);
  CHECK(L_pos.get_iesimo(5)==4);
}

void test6(){
  BST arvore = BST();
  arvore.inserir_elemento(7);
  arvore.inserir_elemento(3);
  arvore.inserir_elemento(2);
  arvore.inserir_elemento(5);
  arvore.inserir_elemento(4);
  arvore.inserir_elemento(6);

  ListaEncadeada L_pre=arvore.pre_ordem();
  CHECK(L_pre.get_iesimo(0)==7);
  CHECK(L_pre.get_iesimo(1)==3);
  CHECK(L_pre.get_iesimo(2)==2);
  CHECK(L_pre.get_iesimo(3)==5);
  CHECK(L_pre.get_iesimo(4)==4);
  CHECK(L_pre.get_iesimo(5)==6);

  ListaEncadeada L_em=arvore.em_ordem();
  CHECK(L_em.get_iesimo(0)==2);
  CHECK(L_em.get_iesimo(1)==3);
  CHECK(L_em.get_iesimo(2)==4);
  CHECK(L_em.get_iesimo(3)==5);
  CHECK(L_em.get_iesimo(4)==6);
  CHECK(L_em.get_iesimo(5)==7);

  ListaEncadeada L_pos=arvore.pos_ordem();
  CHECK(L_pos.get_iesimo(0)==2);
  CHECK(L_pos.get_iesimo(1)==4);
  CHECK(L_pos.get_iesimo(2)==6);
  CHECK(L_pos.get_iesimo(3)==5);
  CHECK(L_pos.get_iesimo(4)==3);
  CHECK(L_pos.get_iesimo(5)==7);
}

int main(){
  test3();
  test4();
  test5();
  test6();
}
