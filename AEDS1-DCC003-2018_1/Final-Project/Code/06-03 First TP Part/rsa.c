/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018

  Documentação de cada método/função pode ser encontrada no arquivo "rsa.h"
*/

/*
  Nesse código temos a declaração de todos os métodos que serão utilizados
  no processo de criptografar/descriptografar mensagens.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rsa.h"

#define MIN_ASCII_VALUE 32 // Space
#define MAX_ASCII_VALUE 127 // DEL

void choose_variables(long p, long q, long *n, long *d, long *e){
  *n = p * q;
  long totient = (p - 1) * (q - 1);

  for(int i = sqrt(totient); i < totient; i++){
    if(greatest_common_divisor(i, totient) == 1){
      *e = i;
      break;
    }
  }

  *d = mul_inv(*e, totient);
}

long * encode_message(long *message_blocks, int block_count, long n, long e){
  long *encoded = malloc(block_count * sizeof(long));
  for(int i = 0; i < block_count; i++){
    encoded[i] = power_mod(message_blocks[i], e, n);
  }

  return encoded;
}

long * decode_message(long *encoded_blocks, int block_count, long n, long d){
  long *message = malloc(block_count * sizeof(long));
  for(int i = 0; i < block_count; i++){
    message[i] = power_mod(encoded_blocks[i], d, n);
  }

  return message;
}

long * break_message_into_blocks(char message[], long n, int *block_count){
  int encoding_base = choose_encoding_base(n);
  char *full_encoded_message = generate_full_message_string(message, encoding_base);

  long *blocks = malloc(strlen(full_encoded_message) * sizeof(long));
  char *current_word = malloc((log10(n) + 2) * sizeof(char));

  int row = 0;
  for(int i = 0; i < strlen(full_encoded_message); i++){
    char* new_block = concat_char(current_word, full_encoded_message[i]);
    long new_block_value = char_to_long(new_block);

    char* next_block = concat_char(new_block, full_encoded_message[i + 1]);
    long next_block_value = char_to_long(next_block);

    if(new_block_value >= n || (full_encoded_message[i + 1] == '0' && next_block_value > n)){
      blocks[row] = char_to_long(current_word);
      row++;
      current_word = malloc((log10(n) + 1) * sizeof(char));
    }

    current_word = concat_char(current_word, full_encoded_message[i]);
  }

  *block_count = row + 1;

  blocks[row] = char_to_long(current_word);

  return blocks;
}

char * build_message_from_blocks(long *decoded_blocks, int block_count, long n){
  int encoding_base = choose_encoding_base(n);
  char *message = malloc(sizeof(char) * block_count * (log(n) + 1));
  char *full_decoded_message = recover_full_message_string(decoded_blocks, block_count, n);

  int base_min_ascii_length = ceil(log(MIN_ASCII_VALUE) / log(encoding_base));

  int char_ascii_length = base_min_ascii_length + 1;
  int last_stop = 0;
  int message_index = 0;
  char *current_word = malloc(char_ascii_length * sizeof(char));
  for(int i = 0; i < strlen(full_decoded_message); i++){
    if(full_decoded_message[i] < MIN_ASCII_VALUE) continue;
    int char_length = base_min_ascii_length;
    if(encoding_base == 5)
      char_length += (full_decoded_message[i] == '1' && full_decoded_message[i + 1] == '0');
    else
      char_length += (full_decoded_message[i] == '1');

    for(; i < last_stop + char_length; i++){
      current_word[i - last_stop] = full_decoded_message[i];
    }

    last_stop = i--;
    message[message_index++] = (int)decode_char(current_word, encoding_base);
    for(int i = 0; i < char_ascii_length; i++) current_word[i] = '\0';
  }

  return message;
}

char * generate_full_message_string(char message[], int encoding_base){
  int m_len = strlen(message);
  char *full_encoded_message = malloc(m_len * 4 * sizeof(char));
  int index = 0;
  for(int i = 0; i < m_len * 2; i += 2){
    char *encoded = encode_char(message[i / 2], encoding_base);

    for(int j = 0; j < strlen(encoded); j++)
      full_encoded_message[index++] = encoded[j];
  }

  return full_encoded_message;
}

char * recover_full_message_string(long *blocks, int block_len, long n){
  char *full_decoded_message = malloc((int)((log10(n) + 1) * block_len) * sizeof(char));
  int index = 0;

  for(int i = 0; i < block_len; i++){
    char *block = long_to_char(blocks[i]);
    for(int j = 0; j < strlen(block); j++)
      full_decoded_message[index++] = block[j];
  }

  return full_decoded_message;
}

long * get_blocks_from_string(char *encoded_message, int *b_count){
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
      for(int j = 0; j < strlen(encoded_message); j++) line[j] = '\0';
      line_index = 0;
    }else{
      line[line_index++] = encoded_message[i];
    }
  }

  return blocks;
}

char * encode_char(long n, int base){
  long octal_n = as_other_base(n, 10, base);
  // Adiciona "11111..." (com floor(log10(octal_n)) 1's) para retirar os 0's
  octal_n += as_other_base(pow(2, floor(log10(octal_n))) - 1, 10, 2);
  return long_to_char(octal_n);
}

long decode_char(char *n, int base){
  int octal_n = char_to_long(n);
  // Retira "11111..." (com floor(log10(octal_n)) 1's) para retirar os 0's
  octal_n -= as_other_base(pow(2, floor(log10(octal_n))) - 1, 10, 2);
  return as_other_base(octal_n, base, 10);
}

int choose_encoding_base(long n){
  if(n <= 9) return n - 1;
  else return 9;
}

long power_mod(long a, long b, long m){
  long p_mod[(int)(log(b) / log(2)) + 1];
  p_mod[0] = a;

  for(int i = 1; i < log(b) / log(2) + 1; i++){
    p_mod[i] = fmodl(powl(p_mod[i - 1], 2), m);
  }

  unsigned long long result = 1;
  while(b >= 1){
    result = fmodl(result * p_mod[(int)(log(b) / log(2))], m);
    b -= powl(2, (int)(log(b) / log(2)));
  }

  return result;
}

long mul_inv(long a, long b){
  long b0 = b, t, q;
  long x0 = 0, x1 = 1;
  if (b == 1) return 1;
  while (a > 1) {
    q = a / b;
    t = b, b = a % b, a = t;
    t = x0, x0 = x1 - q * x0, x1 = t;
  }
  if (x1 < 0) x1 += b0;
  return x1;
}

long greatest_common_divisor(long a, long b){
  if (a == 0 || b == 0) return 0;
  if (a == b) return a;
  if (a > b) return greatest_common_divisor(a - b, b);
  return greatest_common_divisor(a, b - a);
}

long as_other_base(long n, int n_base, int to_base){
  int other_n = 0;
  int k = n;
  int i = 1;

  while(k != 0){
    other_n += k % 10 * i;
    k /= 10;
    i *= n_base;
  }

  k = other_n;
  other_n = 0;
  i = 1;

  while(k != 0){
    other_n += k % to_base * i;
    k /= to_base;
    i *= 10;
  }

  return other_n;
}

char * long_to_char(long n){
  int n_log;
  if(n > 0) n_log = log10(n) + 2;
  else n_log = 2;
  char *number_array = (char *)malloc(n_log * sizeof(char));
  sprintf(number_array, "%ld", n);
  return number_array;
}

long char_to_long(char *c){
  return atol(c);
}

char * concat_char(const char *s, const char c){
  char *result = malloc(strlen(s) + 2);
  for(int i = 0; i < strlen(s); i++) result[i] = s[i];
  result[strlen(s)] = c;
  return result;
}
