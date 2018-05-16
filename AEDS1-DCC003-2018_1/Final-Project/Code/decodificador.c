#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rsa.h"

#define MAX_PRIVATE_TXT_SIZE 64

long * read_variables_from_file(char *file_path);
long * get_blocks(char *encoded_message, int *block_count);

int main(int argc, char* argv[]) {
  char *encoded_message = argv[1];
  char sep = argv[2][0];
  char *private_file_path = argv[3];

  int m_len = strlen(encoded_message);

  long *private_keys = read_variables_from_file(private_file_path);

  int block_count = 0;
  long *encoded_blocks = get_blocks(encoded_message, &block_count);

  long *decoded_m = decode_message(encoded_blocks, block_count, private_keys[0], private_keys[1]);

  char *retrieved_message = build_message_from_blocks(decoded_m, block_count, private_keys[0]);

  printf("Message decoded:\n%s\n", retrieved_message);

  return 0;
}

long * read_variables_from_file(char *file_path){
  long *variables = malloc(3 * sizeof(long));
  int variable_index = 0;

  FILE *file = fopen(file_path, "r");

  if (file == NULL){
      printf("Could not open file %s", file_path);
      exit(1);
  }

  char c;
  char *line = malloc(MAX_PRIVATE_TXT_SIZE * sizeof(char));
  int line_index = 0;

  while((c = fgetc(file)) != EOF){
    if(c != '\n'){
      line[line_index++] = c;
    }else{
      variables[variable_index++] = atol(line);
      line_index = 0;
      for(int j = 0; j < MAX_PRIVATE_TXT_SIZE; j++) line[j] = '\0';
    }
  }

  variables[variable_index++] = atol(line);

  fclose(file);

  return variables;
}

long * get_blocks(char *encoded_message, int *b_count){
  int block_count = 0;

  for(int i = 0; i < strlen(encoded_message); i++){
    if(encoded_message[i] == '/') block_count++;
  }

  *b_count = block_count;

  long *blocks = malloc(block_count * sizeof(long));
  int block_index = 0;

  char *line = malloc(strlen(encoded_message) * sizeof(char));
  int line_index = 0;

  for(int i = 0; i < strlen(encoded_message); i++){
    if(encoded_message[i] == '/'){
      blocks[block_index++] = atol(line);
      for(int j = 0; j < MAX_PRIVATE_TXT_SIZE; j++) line[j] = '\0';
      line_index = 0;
    }else{
      line[line_index++] = encoded_message[i];
    }
  }

  return blocks;
}
