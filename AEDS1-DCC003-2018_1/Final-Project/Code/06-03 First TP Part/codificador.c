/*
  Autor: Lucas Pellegrinelli
  Data: 19/05/2018

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

/*
  Gera o arquivo 'private.txt' com os valores das variáveis recebidas

  Entrada:
  'n' -> Variável calculada no método 'choose_variables'
  'd' -> Variável calculada no método 'choose_variables'
*/
void write_variables_to_file(long n, long d);

/*
  Testa se um número é primo

  Entrada:
  'n' -> Número a ser testado

  Saída:
  'return' -> '0' se o número nao for primo e '1' caso ela seja primo
*/
int is_prime(long n);

int main(int argc, char* argv[]) {
  if(argc <= 2){
    printf("Você esqueceu algumas informações. Lembre que o comando tem que receber a mensagem, o 'p', e o 'q'.\n");
    exit(1);
  }else if(strlen(argv[1]) == 0){
    printf("A mensagem informada tem tamanho 0, favor corrigir a mensagem informada.\n");
    exit(1);
  }else if(is_prime(atol(argv[2])) == 0 || is_prime(atol(argv[3])) == 0){
    printf("Um (ou os dois) dos números informados não são primos.\n");
    exit(1);
  }else if(atol(argv[2]) <= 2 || atol(argv[3]) <= 2){
    printf("Os primos tem que ser pelo menos 3.\n");
    exit(1);
  }else if(atol(argv[2]) * atol(argv[3]) < 3037000499){
    printf("O produto entre os primos tem que ser menor que 3037000499 (raiz quadrada do valor máximo de um long).\n");
    exit(1);
  }

  char *message = argv[1];
  int m_len = strlen(message);

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
      printf("Não foi possível abrir o arquivo.\n");
      exit(1);
  }

  fprintf(file, "%ld\n%ld", n, d);
  fclose(file);
}

int is_prime(long n) {
  if(n == 2) return 1;
	if (n % 2 == 0 || n <= 1) return 0;

	for (int i = 3; i < sqrt(n); i += 2){
		if (n % i == 0) return 0;
	}

	return 1;
}
