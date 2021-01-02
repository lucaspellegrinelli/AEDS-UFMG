#include "intlist.h"
#include "stringlist.h"
#include "usertags.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  struct usertags* head = NULL;

  usertags_add(&head, 0);
  struct intlist ** user0_list = usertags_get(head, 0);
  intlist_add(user0_list, 0);
  intlist_add(user0_list, 1);

  usertags_add(&head, 1);
  struct intlist ** user1_list = usertags_get(head, 1);
  intlist_add(user1_list, 2);
  intlist_add(user1_list, 3);

  usertags_add(&head, 2);
  struct intlist ** user2_list = usertags_get(head, 2);
  intlist_add(user2_list, 4);
  intlist_add(user2_list, 5);

  for(int i = 0; i < usertags_size(head); i++){
    struct intlist ** user_list = usertags_get(head, i);

    printf("User: %d ", i);
    for(int j = 0; j < intlist_size(*user_list); j++){
      printf(" %d", intlist_ith(*user_list, j));
    }
    printf("\n");
	}
}