#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* PROTÓTIPOS */
void choose_variables(long p, long q, long *n, long *d, long *e);

long * encode_message(long *message_blocks, int block_count, long n, long e);
long * decode_message(long *encoded_blocks, int block_count, long n, long d);

long * break_message_into_blocks(char message[], int m_len, long n, int *block_count);
char * build_message_from_blocks(long *decoded_blocks, int block_count, int n);
char * generate_full_message_string(char message[], int m_len);
char * recover_full_message_string(long *blocks, int block_len, int n);

char * encode_char(long n);
long decode_char(char *c);

long power_mod(long a, long b, long m);
int mul_inv(int a, int b);
long greatest_common_divisor(long a, long b);

int * string_to_int(char str[], int str_len);
char * concat_char(const char *s1, const char c);
/* FINAL PROTÓTIPOS */

int main() {
  char message[] = "This is a test";
  int m_len = sizeof message - 1;
  long p = 25073;
  long q = 25087;
  long e = 1;
  long d;
  long n;

  choose_variables(p, q, &n, &d, &e);
  printf("Variables:\n");
  printf("p = %ld\n", p);
  printf("q = %ld\n", q);
  printf("n = %ld\n", n);
  printf("d = %ld\n", d);
  printf("e = %ld\n", e);
  printf("\n");

  printf("Original message:\n");
  for(int i = 0; i < m_len; i++){
    printf("%c", message[i]);
  }
  printf("\n\n");

  int block_count;
  long *message_blocks = break_message_into_blocks(message, m_len, n, &block_count);
  long *encoded_m = encode_message(message_blocks, block_count, n, e);

  long *decoded_m = decode_message(encoded_m, block_count, n, d);
  char *retrieved_message = build_message_from_blocks(decoded_m, block_count, n);

  printf("Message/Encoded/Decoded:\n");
  for(int i = 0; i < block_count; i++){
    printf("%ld    %ld   %ld\n", message_blocks[i], encoded_m[i], decoded_m[i]);
  }
  printf("\n\n");

  printf("Retrieved message:\n");
  for(int i = 0; i < m_len; i++){
    printf("%c", retrieved_message[i]);
  }
  printf("\n");
}

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
  long *messageHex = malloc(block_count * sizeof(long));
  for(int i = 0; i < block_count; i++){
    messageHex[i] = power_mod(encoded_blocks[i], d, n);
  }

  return messageHex;
}

long * break_message_into_blocks(char message[], int m_len, long n, int *block_count){
  char *full_encoded_message = generate_full_message_string(message, m_len);

  long *blocks = malloc(strlen(full_encoded_message) * sizeof(long));
  char *current_word = malloc((log10(n) + 1) * sizeof(char));

  int row = 0;
  for(int i = 0; i < strlen(full_encoded_message); i++){
    char* new_block = concat_char(current_word, full_encoded_message[i]);
    long new_block_value = decode_char(new_block);

    char* next_block = concat_char(new_block, full_encoded_message[i + 1]);
    long next_block_value = decode_char(next_block);

    if(new_block_value > n || (full_encoded_message[i + 1] == '0' && next_block_value > n)){
      blocks[row] = decode_char(current_word);
      row++;
      current_word = malloc((log10(n) + 1) * sizeof(char));
    }

    current_word = concat_char(current_word, full_encoded_message[i]);
  }

  *block_count = row + 1;

  blocks[row] = decode_char(current_word);

  return blocks;
}

char * build_message_from_blocks(long *decoded_blocks, int block_count, int n){
  char *message = malloc(sizeof(char) * block_count * (log(n) + 1));
  char *full_decoded_message = recover_full_message_string(decoded_blocks, block_count, n);

  int char_ascii_length = 3;
  int last_stop = 0;
  int message_index = 0;
  char *current_word = malloc(char_ascii_length * sizeof(char));
  for(int i = 0; i < strlen(full_decoded_message); i++){
    int char_length = 2 + (full_decoded_message[i] == '1');

    for(; i < last_stop + char_length; i++){
      current_word[i - last_stop] = full_decoded_message[i];
    }

    last_stop = i--;
    message[message_index++] = (int)decode_char(current_word);
    for(int i = 0; i < char_ascii_length; i++) current_word[i] = '\0';
  }

  return message;
}

char * generate_full_message_string(char message[], int m_len){
  char *full_encoded_message = malloc(m_len * 4 * sizeof(char));
  int index = 0;
  for(int i = 0; i < m_len * 2; i += 2){
    char *encoded = encode_char(message[i / 2]);

    for(int j = 0; j < strlen(encoded); j++)
      full_encoded_message[index++] = encoded[j];
  }

  return full_encoded_message;
}

char * recover_full_message_string(long *blocks, int block_len, int n){
  char *full_decoded_message = malloc((log10(n) + 1) * block_len * sizeof(char));

  int index = 0;
  for(int i = 0; i < block_len; i++){
    char *block = encode_char(blocks[i]);

    for(int j = 0; j < strlen(block); j++)
      full_decoded_message[index++] = block[j];
  }

  return full_decoded_message;
}

char * encode_char(long n){
  long n_log = log10(n) + 2;
  char *number_array = malloc(n_log * sizeof(char));
  snprintf(number_array, n_log, "%ld", n);
  return number_array;
}

long decode_char(char *c){
  return atoi(c);
}

long power_mod(long a, long b, long m){
  long p_mod[(int)(log(b) / log(2))];
  p_mod[0] = a;
  for(int i = 1; i < log(b) / log(2); i++){
    p_mod[i] = fmodl(powl(p_mod[i - 1], 2), m);
  }

  long result = 1;
  while(b >= 1){
    result = fmodl(result * p_mod[(int)(log(b) / log(2))], m);
    b -= powl(2, (int)(log(b) / log(2)));
  }

  return result;
}

int mul_inv(int a, int b){
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
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

int * string_to_int(char str[], int str_len){
  int *arr = malloc(str_len);

  for(int i = 0; i < str_len; i++){
    arr[i] = str[i];
  }

  return arr;
}

char * concat_char(const char *s1, const char c){
  char *result = malloc(strlen(s1) + 2);
  for(int i = 0; i < strlen(s1); i++) result[i] = s1[i];
  result[strlen(s1)] = c;
  return result;
}
