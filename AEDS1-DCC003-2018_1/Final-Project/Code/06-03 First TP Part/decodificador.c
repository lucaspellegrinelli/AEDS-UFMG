/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018

  Documentação de cada método/função não declarado nesse arquivo pode ser
  encontrada no arquivo "rsa.h"
*/

/*
  Nesse código temos a interface com o usuário na hora de descriptografar
  uma mensagem.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rsa.h"

/*
  Número máximo de caracteres a serem lidos do arquivo 'private.txt'
*/
#define MAX_PRIVATE_TXT_SIZE 64

/*
  Lê os valores de 'n' e 'd' salvos no arquivo 'private.txt' indicado

  Entrada:
  'file_path' -> Caminho para o arquivo 'private.txt'

  Saída:
  'return' -> Valores para 'n' e 'd', um em cada posição do vetor
*/
long * read_variables_from_file(char *file_path);

int main(int argc, char* argv[]) {
  if(argc <= 2){
    printf("Você esqueceu algumas informações. Lembre que o comando tem que receber a mensagem criptografada e o caminho para o arquivo 'private.txt'.\n");
    exit(1);
  }else if(strlen(argv[1]) == 0){
    printf("A mensagem informada tem tamanho 0, favor corrigir a mensagem informada.\n");
    exit(1);
  }else if(strlen(argv[2]) == 0){
    printf("O caminho para o arquivo tem tamanho 0, portanto o programa não conseguirá acessar 'd' e 'n', favor corrigir o caminho.\n");
    exit(1);
  }

  char *encoded_message = argv[1];
  char *private_file_path = argv[2];

  int m_len = strlen(encoded_message);

  long *private_keys = read_variables_from_file(private_file_path);

  int block_count = 0;
  long *encoded_blocks = get_blocks_from_string(encoded_message, &block_count);

  long *decoded_m = decode_message(encoded_blocks, block_count, private_keys[0], private_keys[1]);

  char *retrieved_message = build_message_from_blocks(decoded_m, block_count, private_keys[0]);

  printf("\nMessage decoded:\n%s\n", retrieved_message);

  return 0;
}

long * read_variables_from_file(char *file_path){
  long *variables = malloc(5 * sizeof(long));
  int variable_index = 0;

  FILE *file = fopen(file_path, "r");

  if (file == NULL){
      printf("Não foi possível abrir o arquivo %s", file_path);
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
