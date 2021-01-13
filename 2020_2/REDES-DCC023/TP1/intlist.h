#ifndef INTLIST_H
#define INTLIST_H

#include <stdlib.h>
#include <stdio.h>

struct intlist {
  int value;
  struct intlist *next;
};

void intlist_add(struct intlist** ref, int value);
void intlist_remove_ith(struct intlist** ref, int i);
void intlist_remove(struct intlist** ref, int value);
int intlist_ith(struct intlist* node, int i);
int intlist_contains(struct intlist* node, int i);
int intlist_size(struct intlist* node);
void intlist_free(struct intlist** node);

#endif