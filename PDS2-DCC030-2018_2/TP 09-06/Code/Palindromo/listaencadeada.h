#ifndef LISTAENCADEADA_H_
#define LISTAENCADEADA_H_

struct node_t {
  int elemento;
  node_t *proximo;
  node_t *anterior;
};

class ListaEncadeada{
private:
  node_t *primeiro;
  node_t *ultimo;
public:
  ListaEncadeada();
  ~ListaEncadeada();
  void insere_elemento(int);
  void insere_primeiro(int);
  int get_iesimo(int);
  void remover_elemento();
  void remover_primeiro();
  void inserir_iesimo(int, int);
  void remover_iesimo(int);
  int tamanho();
  bool checa_palindromo();
};

#endif
