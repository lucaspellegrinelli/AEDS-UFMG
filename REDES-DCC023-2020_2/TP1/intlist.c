#include "intlist.h"

void intlist_add(struct intlist** ref, int value) {
  struct intlist* new_node = (struct intlist*)malloc(sizeof(struct intlist));
  struct intlist* last = *ref;

  new_node->value = value;
  new_node->next = NULL;

  if (*ref == NULL) {
    *ref = new_node;
    return;
  }

  while (last->next != NULL)
    last = last->next;

  last->next = new_node;
  return;
}

void intlist_remove_ith(struct intlist** ref, int i) {
  struct intlist *temp = *ref, *prev;

  int count = 0;
  if (temp != NULL && count == i) {
    *ref = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && count != i) {
    prev = temp;
    temp = temp->next;
    count++;
  }

  if (temp == NULL) return;
  prev->next = temp->next;
  free(temp);
}

void intlist_remove(struct intlist** ref, int value) {
  struct intlist *temp = *ref, *prev;

  int count = 0;
  if (temp != NULL && temp->value == value) {
    *ref = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && temp->value != value) {
    prev = temp;
    temp = temp->next;
    count++;
  }

  if (temp == NULL) return;
  prev->next = temp->next;
  free(temp);
}

int intlist_ith(struct intlist* node, int i){
  int count = 0;
  while(node != NULL && node->next != NULL && count++ < i){
    node = node->next;
  }

  if(node == NULL){
    return -1;
  }

  return node->value;
}

int intlist_contains(struct intlist* node, int value){
  while(node != NULL && node->value != value){
    node = node->next;
  }

  if(node == NULL) return 0;
  return 1;
}

int intlist_size(struct intlist* node){
  int count = 0;
  while (node != NULL){
    count++;
    node = node->next;
  }
  return count;
}

void intlist_free(struct intlist** node){
  for(int i = intlist_size(*node) - 1; i >= 0; i--){
    intlist_remove_ith(node, i);
  }
}