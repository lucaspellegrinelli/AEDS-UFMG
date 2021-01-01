#include "tag.h"

extern int all_tags_size = 0;

int get_tag_id(char *tag){
  for(int i = 0; i < all_tags_size; i++){
    if(strcmp(all_tags[i], tag) == 0){
      return i;
    }
  }

  return -1;
}

int create_tag(char *tag){
  all_tags[all_tags_size] = (char*) malloc(strlen(tag) * sizeof(char));
  strcpy(all_tags[all_tags_size], tag);
  all_tags_size++;
  return all_tags_size - 1;
}

int add_tag_to_user(int *user_tags, char *tag){
  int tag_id = get_tag_id(tag);

  if(tag_id == -1){ // Se a tag ainda não existe, crie
    tag_id = create_tag(tag);
  }

  int is_alredy_sub = 0;
  for(int i = 0; i < MAX_USER_TAGS; i++){
    if(user_tags[i] == tag_id){
      is_alredy_sub = 1;
      break;
    }
  }

  if(is_alredy_sub == 0){ // Se ele não é inscrito na tag, increva-o
    for(int i = 0; i < MAX_USER_TAGS; i++){
      if(user_tags[i] == -1){
        user_tags[i] = tag_id;
        break;
      }
    }
  }

  return is_alredy_sub;
}

int remove_tag_to_user(int *user_tags, char *tag){
  int tag_id = get_tag_id(tag);

  if(tag_id == -1){ // Se a tag ainda não existe, returne que o usuario nao tem a tag
    return 0;
  }

  int is_alredy_sub = 0;
  for(int i = 0; i < MAX_USER_TAGS; i++){
    if(user_tags[i] == tag_id){
      is_alredy_sub = 1;
      break;
    }
  }

  if(is_alredy_sub == 1){ // Se ele é inscrito na tag, desinsncreva-o
    for(int i = 0; i < MAX_USER_TAGS; i++){
      if(user_tags[i] == tag_id){
        user_tags[i] = -1;
        break;
      }
    }
  }

  return is_alredy_sub;
}