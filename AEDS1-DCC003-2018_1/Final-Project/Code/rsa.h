void choose_variables(long p, long q, long *n, long *d, long *e);

long * encode_message(long *message_blocks, int block_count, long n, long e);
long * decode_message(long *encoded_blocks, int block_count, long n, long d);

long * break_message_into_blocks(char message[], int m_len, long n, int *block_count);
char * build_message_from_blocks(long *decoded_blocks, int block_count, long n);
char * generate_full_message_string(char message[], int m_len);
char * recover_full_message_string(long *blocks, int block_len, long n);

char * encode_char(long n);
long decode_char(char *c);

long power_mod(long a, long b, long m);
long mul_inv(long a, long b);
long greatest_common_divisor(long a, long b);

int * string_to_int(char str[], int str_len);
char * concat_char(const char *s1, const char c);