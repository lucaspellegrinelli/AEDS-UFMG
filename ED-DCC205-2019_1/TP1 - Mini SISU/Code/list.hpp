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
  int pivot_pos;
  node_t<T> *pivot;

public:
  List(){
    this->first = nullptr;
    this->last = nullptr;
    this->length = 0;
    this->pivot_pos = -1;
    this->pivot = nullptr;
  }

  void insert_ordered(T elem){
    if(this->length == 0){
      this->insert_beginning(elem);
    }else if(elem >= this->last->value){
      this->insert_end(elem);
    }else{
      for(int i = 0; i < this->length; i++){
        node_t<T> *curr_node = this->move_pivot(i);
        if(curr_node->value >= elem){
          this->insert(elem, i);
          break;
        }
      }
    }
  }

  void insert_ordered_course(T elem, int course){
    if(this->length == 0){
      this->insert_beginning(elem);
    }else if(elem >= this->last->value){
      this->insert_end(elem);
    }else{
      bool added = false;
      for(int i = 0; i < this->length; i++){
        node_t<T> *curr_node = this->move_pivot(i);
        if(curr_node->value.more_equal(elem, course)){
          this->insert(elem, i);
          added = true;
          break;
        }
      }

      if(!added) this->insert_end(elem);
    }
  }

  T get(int pos){
    if(pos >= 0 && pos < this->length){
      node_t<T> *curr_node = this->move_pivot(pos);
      return curr_node->value;
    }else{
      throw std::runtime_error("The get position (" + std::to_string(pos) + ") is outside bounds");
    }
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
    node_t<T> *current_node = this->first;
    node_t<T> *next_node;

    while (current_node != 0) {
      next_node = current_node->next;
      delete current_node;
      current_node = next_node;
    }
  }
};

#endif
