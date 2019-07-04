#ifndef TREE
#define TREE

#include <string>
#include <iostream>

class Node{
public:
  std::string key;
  std::string value;
  Node *point;
  Node *line;

  Node(){
    this->key = "";
    this->value = "";
    this->point = nullptr;
    this->line = nullptr;
  }

  ~Node(){
    delete this->point;
    delete this->line;
  }

  void pre_order(){
    if(this->key != ""){
      std::cout << this->value << " " << this->key << std::endl;
    }

    if(this->point) this->point->pre_order();
    if(this->line) this->line->pre_order();
  }
};

class Tree{
public:
  Node *root;

  Tree(){
    this->root = new Node();
  }

  ~Tree(){
    delete root;
  }

  void insert(std::string key, std::string value){
    Node *curr_node = root;

    for(unsigned int i = 0; i < key.size(); i++){
      if(key[i] == '.'){
        if(!curr_node->point) curr_node->point = new Node();
        curr_node = curr_node->point;
      }else if(key[i] == '-'){
        if(!curr_node->line) curr_node->line = new Node();
        curr_node = curr_node->line;
      }
    }

    curr_node->key = key;
    curr_node->value = value;
  }

  std::string search(std::string key){
    Node *curr_node = root;

    for(unsigned int i = 0; i < key.size(); i++){
      if(key[i] == '.'){
        if(!curr_node->point) return "";
        curr_node = curr_node->point;
      }else if(key[i] == '-'){
        if(!curr_node->line) return "";
        curr_node = curr_node->line;
      }
    }

    return curr_node->value;
  }

  void pre_order(){
    if(this->root) this->root->pre_order();
  }
};

#endif
