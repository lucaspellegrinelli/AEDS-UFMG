#include "tag.h"

struct stringlist* all_tags = NULL;
struct usertags* user_tags = NULL;

int add_tag_to_user(int user, char *tag){
  struct intlist ** curr_user = usertags_get(user_tags, user);
  int tag_id = stringlist_find(all_tags, tag);

  if(tag_id == -1){ // Se a tag ainda não existe, crie
    stringlist_add(&all_tags, tag);
    tag_id = stringlist_size(all_tags);
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

  for(int i = 0; i < strlen(msg); i++){
    if(msg[i - 1] == ' ' && msg[i] == '#' && i < strlen(msg) - 1){
      for(int j = i + 1; j < strlen(msg); j++){
        if(msg[j + 1] == ' ' || j == strlen(msg) - 1){
          // Se depois de #texto tiver um espaço ou fim do texto, entao é uma tag valida
          char tag_str[j - i];
          memcpy(tag_str, msg + i + 1, j - i);
          intlist_add(tag_ids, stringlist_find(all_tags, tag_str));
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