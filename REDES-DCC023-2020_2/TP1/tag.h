#ifndef TAG_H
#define TAG_H

#include <string.h>
#include <stdlib.h>

#define MAX_TAGS 128
#define MAX_USER_TAGS 128

char *all_tags[MAX_TAGS];
extern int all_tags_size;

int get_tag_id(char *tag);
int create_tag(char *tag);
int add_tag_to_user(int *user_tags, char *tag);
int remove_tag_to_user(int *user_tags, char *tag);

#endif