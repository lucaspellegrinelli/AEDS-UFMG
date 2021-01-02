#ifndef STRINGLIST_H
#define STRINGLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stringlist {
  char * value;
  struct stringlist *next;
};

void stringlist_add(struct stringlist** ref, char* value);
void stringlist_remove_ith(struct stringlist** ref, int i);
int stringlist_ith(struct stringlist* node, int i, char* out);
int stringlist_find(struct stringlist* node, char* value);
int stringlist_size(struct stringlist* node);
void stringlist_free(struct stringlist** node);

#endif