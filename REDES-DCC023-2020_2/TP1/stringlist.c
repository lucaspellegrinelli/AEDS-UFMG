#include "stringlist.h"

void stringlist_add(struct stringlist** ref, char* value) {
  struct stringlist* new_node = (struct stringlist*)malloc(sizeof(struct stringlist));
  struct stringlist* last = *ref;

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

void stringlist_remove_ith(struct stringlist** ref, int i) {
  struct stringlist *temp = *ref, *prev;

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

int stringlist_ith(struct stringlist* node, int i, char* out){
  int count = 0;
  while(node != NULL && node->next != NULL && count++ < i){
    node = node->next;
  }

  if(node == NULL){
    return -1;
  }

  memcpy(out, node->value, strlen(node->value));
  return 0;
}

int stringlist_find(struct stringlist* node, char* value){
  int count = 0;
  while(node != NULL && node->next != NULL && strcmp(node->value, value) != 0){
    node = node->next;
    count++;
  }

  if(node == NULL){
    return -1;
  }

  return count;
}

int stringlist_size(struct stringlist* node){
  int count = 0;
  while (node != NULL){
    count++;
    node = node->next;
  }
  return count;
}

void stringlist_free(struct stringlist** node){
  for(int i = stringlist_size(*node) - 1; i >= 0; i--){
    stringlist_remove_ith(node, i);
  }
}