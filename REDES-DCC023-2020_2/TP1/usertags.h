#ifndef TAGLIST_H
#define TAGLIST_H

#include "intlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

struct usertags {
  int user;
  pthread_t thread_id;
  struct intlist *value;
  struct usertags *next;
};

void usertags_add(struct usertags** ref, int user, pthread_t thread_id);
void usertags_remove(struct usertags** ref, int user);
void usertags_remove_ith(struct usertags** ref, int i);
struct intlist ** usertags_get(struct usertags* node, int user);
struct intlist ** usertags_get_ith(struct usertags* node, int i);
int usertags_get_ith_key(struct usertags* node, int i);
pthread_t usertags_get_ith_thread(struct usertags* node, int i);
int usertags_size(struct usertags* node);
void usertags_free(struct usertags** node);

#endif