#include "usertags.h"

void usertags_add(struct usertags** ref, int user, pthread_t thread_id) {
  struct usertags* last = *ref;

  if (*ref == NULL) {
    *ref = (struct usertags*) malloc(sizeof(struct usertags));
    (*ref)->user = user;
    (*ref)->thread_id = thread_id;
    (*ref)->value = NULL;
    (*ref)->next = NULL;
    return;
  }

  while (last->next != NULL) last = last->next;

  last->next = (struct usertags*) malloc(sizeof(struct usertags));
  last->next->user = user;
  last->next->thread_id = thread_id;
  last->next->value = NULL;
  last->next->next = NULL;
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

struct intlist ** usertags_get_ith(struct usertags* node, int i){
  int count = 0;
  while(node != NULL && node->next != NULL && count != i){
    node = node->next;
    count++;
  }

  if(node == NULL) return NULL;
  return &node->value;
}

int usertags_get_ith_key(struct usertags* node, int i){
  int count = 0;
  while(node != NULL && node->next != NULL && count != i){
    node = node->next;
    count++;
  }

  if(node == NULL) return -1;
  return node->user;
}

pthread_t usertags_get_ith_thread(struct usertags* node, int i){
  int count = 0;
  while(node != NULL && node->next != NULL && count != i){
    node = node->next;
    count++;
  }

  if(node == NULL) return -1;
  return node->thread_id;
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