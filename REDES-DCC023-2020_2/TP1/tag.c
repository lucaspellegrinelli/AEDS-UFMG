#include "tag.h"

struct stringlist* all_tags = NULL;
struct usertags* user_tags = NULL;

int add_tag_to_user(int user, char *tag){
  struct intlist ** curr_user = usertags_get(user_tags, user);
  int tag_id = stringlist_find(all_tags, tag);

  if(tag_id == -1){ // Se a tag ainda não existe, crie
    stringlist_add(&all_tags, tag);
    // tag_id = stringlist_size(all_tags) - 1;
    tag_id = stringlist_find(all_tags, tag);
  }

  int is_alredy_sub = intlist_contains(*curr_user, tag_id);

  if(is_alredy_sub == 0){ // Se ele não é inscrito na tag, increva-o
    intlist_add(curr_user, tag_id);
  }

  return is_alredy_sub;
}

int remove_tag_to_user(int user, char *tag){
  struct intlist ** curr_user = usertags_get(user_tags, user);
  int tag_id = stringlist_find(all_tags, tag);

  if(tag_id == -1){ // Se a tag ainda não existe, returne que o usuario nao tem a tag
    return 0;
  }

  int is_alredy_sub = intlist_contains(*curr_user, tag_id);

  if(is_alredy_sub == 1){ // Se ele é inscrito na tag, desinsncreva-o
    intlist_remove(curr_user, tag_id);
  }

  return is_alredy_sub;
}

int get_all_tags_in_msg(char *msg, struct intlist ** tag_ids){
  int tag_count = 0;

  // printf("First of all, here are all the tags:\n");
  for(int i = 0; i < stringlist_size(all_tags); i++){
    int str_size = stringlist_ith_size(all_tags, i);
    char t[str_size];
    stringlist_ith(all_tags, i, t);
    t[str_size - 1] = '\0';

    // printf(" > %s [", t);
    // for(int j = 0; j < str_size; j++){
    //   printf("%d ", t[j]);
    // }
    // printf("]\n");
  }

  // printf("Secondly, here are the tags found in the message:\n");
  for(int i = 0; i < strlen(msg); i++){
    if(msg[i - 1] == ' ' && msg[i] == '#' && i < strlen(msg) - 1){
      for(int j = i + 1; j < strlen(msg); j++){
        if(msg[j + 1] == ' ' || j == strlen(msg) - 1){
          // Se depois de #texto tiver um espaço ou fim do texto, entao é uma tag valida
          int s = j - i;
          char tag_str[s];
          memcpy(tag_str, msg + i + 1, s);
          tag_str[s - 1] = '\0';

          // printf(" > %s [", tag_str);
          // for(int k = 0; k < s; k++){
          //   printf("%d ", tag_str[k]);
          // }
          // printf("]\n");

          intlist_add(tag_ids, stringlist_find(all_tags, tag_str));
          tag_count++;
          i = j;
          break;
        }else if(msg[j] == '#'){
          // Se antes de um espaço tiver outro #, entao a tag não é valida
          i = j;
          break;
        }
      }
    }
  }

  return tag_count;
}

int get_all_users_sub(struct intlist ** tag_ids, struct intlist ** subbed_users){
  int count = 0;

  printf("Listing all users:\n");
  for(int i = 0; i < usertags_size(user_tags); i++){
    struct intlist ** user_tag = usertags_get_ith(user_tags, i);
    int user_id = usertags_get_ith_key(user_tags, i);

    printf(" > User #%d:", user_id);
    for(int j = 0; j < intlist_size(*user_tag); j++){
      printf(" %d", intlist_ith(*user_tag, j));
    }
    printf("\n");

    for(int x = 0; x < intlist_size(*user_tag); x++){
      for(int y = 0; y < intlist_size(*tag_ids); y++){
        if(intlist_ith(*user_tag, x) == intlist_ith(*tag_ids, y)){
          intlist_add(subbed_users, user_id);
          count++;
          break;
        }
      }
    }
  }

  return count;
}