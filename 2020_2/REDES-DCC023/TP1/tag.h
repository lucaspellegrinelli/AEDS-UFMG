#ifndef TAG_H
#define TAG_H

#include "stringlist.h"
#include "intlist.h"
#include "usertags.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern struct stringlist* all_tags;
extern struct usertags* user_tags;

int get_tag_id(char *tag);
int create_tag(char *tag);
int add_tag_to_user(int user, char *tag);
int remove_tag_to_user(int user, char *tag);
int get_all_tags_in_msg(char *msg, struct intlist ** tag_ids);
int get_all_users_sub(struct intlist ** tag_ids, struct intlist ** subbed_users);

#endif