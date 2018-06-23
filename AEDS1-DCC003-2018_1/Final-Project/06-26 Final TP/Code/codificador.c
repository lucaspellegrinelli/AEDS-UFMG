/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018

  Documentação de cada método/função não declarado nesse arquivo pode ser
  encontrada no arquivo "rsa.h"
*/

/*
  Nesse código temos a interface com o usuário na hora de criptografar
  uma mensagem.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rsa.h"
#include "steganography.h"
#include "PPMIO.h"

/*
  Gera o arquivo 'private.txt' com os valores das variáveis recebidas

  Entrada:
  'n' -> Variável calculada no método 'choose_variables'
  'd' -> Variável calculada no método 'choose_variables'
*/
void write_variables_to_file(long n, long d);

int main(int argc, char* argv[]) {
  if(argc <= 4){
    printf("Você esqueceu algumas informações. Lembre que o comando tem que receber o caminho para a imagem de entrada, a mensagem, o caminhi para a imagem de saída, o 'p', e o 'q'.\n");
    exit(1);
  }else if(strlen(argv[2]) == 0){
    printf("A mensagem informada tem tamanho 0, favor corrigir a mensagem informada.\n");
    exit(1);
  }else if(is_prime(char_to_long(argv[4])) == 0 || is_prime(char_to_long(argv[5])) == 0){
    printf("Um (ou os dois) dos números informados não são primos.\n");
    exit(1);
  }else if(char_to_long(argv[4]) * char_to_long(argv[5]) >= 4294967296){
    printf("O produto entre os primos tem que ser menor que 4294967296 (raiz quadrada do valor máximo de um unsigned long).\n");
    exit(1);
  }else if(char_to_long(argv[4]) == char_to_long(argv[5])){
    printf("Os primos informados não podem ser iguais. Tente novamente escolhendo outros primos.\n");
    exit(1);
  }

  char *input_image_path = argv[1];
  char *output_image_path = argv[3];

  char *message = argv[2];
  int m_len = strlen(message);

  long p = char_to_long(argv[4]);
  long q = char_to_long(argv[5]);
  long e = 1;
  long d;
  long n;

  choose_variables(p, q, &n, &d, &e);

  int block_count;
  long *message_blocks = break_message_into_blocks(message, n, &block_count);

  long *encoded_m = encode_message(message_blocks, block_count, n, e);

  write_variables_to_file(n, d);

  /* ----- Esteganografia ----- */

  struct Image original_image = read_image(input_image_path);
  struct Image encoded_image = hide_message_in_image(original_image, encoded_m, block_count, n, '.');
  write_image(encoded_image, output_image_path);

  return 0;
}

void write_variables_to_file(long n, long d){
  FILE *file = fopen("private.txt", "w");

  if (file == NULL){
      printf("Não foi possível abrir o arquivo.\n");
      exit(1);
  }

  fprintf(file, "%ld\n%ld", n, d);
  fclose(file);
}
