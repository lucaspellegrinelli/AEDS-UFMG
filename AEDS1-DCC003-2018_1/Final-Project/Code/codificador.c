#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rsa.h"

void write_variables_to_file();

int main(int argc, char* argv[]) {
  char *message = argv[1];
  int m_len = strlen(message);

  /* (p * q) < sqrt(MAX_LONG_VALUE) */
  long p = atol(argv[2]);
  long q = atol(argv[3]);
  long e = 1;
  long d;
  long n;

  choose_variables(p, q, &n, &d, &e);

  int block_count;
  long *message_blocks = break_message_into_blocks(message, m_len, n, &block_count);
  long *encoded_m = encode_message(message_blocks, block_count, n, e);

  write_variables_to_file(n, d);

  printf("\nMessage Encoded:\n");
  for(int i = 0; i < block_count; i++){
    printf("%ld/", encoded_m[i]);
  }
  printf("\n");

  return 0;
}

void write_variables_to_file(long n, long d){
  FILE *file = fopen("private.txt", "w");

  if (file == NULL){
      printf("Error opening file!\n");
      exit(1);
  }

  fprintf(file, "%ld\n%ld", n, d);
  fclose(file);
}