#include "usertags.h"

void usertags_add(struct usertags** ref, int user) {
  struct usertags* new_node = (struct usertags*)malloc(sizeof(struct usertags));
  struct usertags* last = *ref;

  new_node->user = user;
  new_node->value = NULL;
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

void usertags_remove(struct usertags** ref, int user) {
  struct usertags *temp = *ref, *prev;

  if (temp != NULL && temp->user == user) {
    *ref = temp->next;
    intlist_free(&temp->value);
    free(temp);
    return;
  }

  while (temp != NULL && temp->user != user) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) return;
  prev->next = temp->next;
  intlist_free(&temp->value);
  free(temp);
}

void usertags_remove_ith(struct usertags** ref, int i) {
  struct usertags *temp = *ref, *prev;

  int count = 0;
  if (temp != NULL && count == i) {
    *ref = temp->next;
    intlist_free(&temp->value);
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
  intlist_free(&temp->value);
  free(temp);
}

struct intlist ** usertags_get(struct usertags* node, int user){
  while(node != NULL && node->next != NULL && node->user != user){
    node = node->next;
  }

  if(node == NULL) return NULL;
  return &node->value;
}

int usertags_size(struct usertags* node){
  int count = 0;
  while (node != NULL){
    count++;
    node = node->next;
  }
  return count;
}

void usertags_free(struct usertags** node){
  for(int i = usertags_size(*node) - 1; i >= 0; i--){
    usertags_remove_ith(node, i);
  }
}