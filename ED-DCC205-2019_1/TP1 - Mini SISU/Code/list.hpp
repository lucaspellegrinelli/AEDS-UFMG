#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T>
struct node_t {
  T value;
  node_t<T> *next;
  node_t<T> *prev;

  node_t(){ }
};

template <class T>
class List{
private:
  node_t<T> *first;
  node_t<T> *last;
  int length;
  bool use_pivot = true;
  int pivot_pos;
  node_t<T> *pivot;

public:
  List(){
    this->first = nullptr;
    this->last = nullptr;
    this->length = 0;
    this->use_pivot = false;
    this->pivot_pos = -1;
    this->pivot = nullptr;
  }

  List(bool use_pivot){
    this->first = nullptr;
    this->last = nullptr;
    this->length = 0;
    this->use_pivot = use_pivot;
    this->pivot_pos = -1;
    this->pivot = nullptr;
  }

  void insert_end(T elem){
    node_t<T> *new_node = new node_t<T>();
    new_node->value = elem;
    new_node->next = nullptr;

    if(this->length == 0){
      new_node->prev = nullptr;
      this->first = new_node;
      this->last = new_node;
    } else{
      new_node->prev = this->last;
      this->last->next = new_node;
      this->last = new_node;
    }

    this->length++;
  }

  void insert_beginning(T elem){
    node_t<T> *new_node = new node_t<T>();
    new_node->value = elem;
    new_node->prev = nullptr;

    if(use_pivot) this->pivot_pos++;

    if(this->length == 0){
      new_node->next = nullptr;
      this->first = new_node;
      this->last = new_node;
    }else{
      new_node->next = this->first;
      this->first->prev = new_node;
      this->first = new_node;
    }

    this->length++;
  }

  void insert(T elem, int pos){
    if(pos >= 0 && pos <= this->length){
      if(this->length == 0 || pos == 0){
        this->insert_beginning(elem);
      }else if(pos == this->length){
        this->insert_end(elem);
      }else{
        node_t<T> *new_node = new node_t<T>();
        new_node->value = elem;
        node_t<T> *curr_node = this->use_pivot ? this->move_pivot(pos) : this->get_node_at(pos);
        new_node->prev = curr_node->prev;
        new_node->prev->next = new_node;
        new_node->next = curr_node;
        new_node->next->prev = new_node;

        if(use_pivot && pos <= this->pivot_pos) this->pivot_pos++;

        this->length++;
      }
    }else{
      throw std::runtime_error("The insert position (" + std::to_string(pos) + ") is outside bounds");
    }
  }

  T get(int pos){
    if(pos >= 0 && pos < this->length){
      node_t<T> *curr_node = this->use_pivot ? this->move_pivot(pos) : this->get_node_at(pos);
      return curr_node->value;
    }else{
      throw std::runtime_error("The get position (" + std::to_string(pos) + ") is outside bounds");
    }
  }

  void remove_last(){
    this->last = this->last->prev;
    delete this->last->next;
    this->last->next = nullptr;

    this->length--;
  }

  void remove_first(){
    this->first = this->first->next;
    delete this->first->prev;
    this->first->prev = nullptr;

    this->length--;
  }

  void remove(int pos){
    if(pos >= 0 && pos < this->length){
      if(pos == 0){
        this->remove_first();
      }else if(pos == this->length - 1){
        this->remove_last();
      }else{
        node_t<T> *curr_node = this->use_pivot ? this->move_pivot(pos) : this->get_node_at(pos);
        curr_node->prev->next = curr_node->next;
        curr_node->next->prev = curr_node->prev;
        delete curr_node;

        this->length--;
      }
    }else{
      throw std::runtime_error("The remove position (" + std::to_string(pos) + ") is outside bounds");
    }
  }

  node_t<T>* get_node_at(int pos){
    node_t<T> *curr_node = this->first;
    while(curr_node != nullptr && pos-- > 0) curr_node = curr_node->next;
    return curr_node;
  }

  node_t<T>* move_pivot(int pos){
    if(this->pivot == nullptr) this->reset_pivot();
    int dist_curr = std::abs(pos - this->pivot_pos);
    int dist_end = this->length - pos - 1;

    if(pos < dist_curr && pos < dist_end){ // Starting from the start is optimal
      this->pivot = this->first;
      this->pivot_pos = 0;
    }else if(dist_end < dist_curr && dist_end < pos){ // Starting from the end is optimal
      this->pivot = this->last;
      this->pivot_pos = this->length - 1;
    }

    int pos_diff = pos - this->pivot_pos;
    if(pos_diff > 0){
      do this->pivot = this->pivot->next;
      while(this->pivot != nullptr && ++this->pivot_pos < pos);
    }else if(pos_diff < 0){
      do this->pivot = this->pivot->prev;
      while(this->pivot != nullptr && --this->pivot_pos > pos);
    }

    return this->pivot;
  }

  void reset_pivot(){
    this->pivot_pos = 0;
    this->pivot = this->first;
  }

  int size(){
    return this->length;
  }

  ~List(){
    node_t<T> *node_prev = nullptr;
    node_t<T> *node_next = this->first;

    while (node_next != nullptr) {
      node_prev = node_next;
      node_next = node_next->next;
      delete node_prev;
    }
  }
};

#endif
