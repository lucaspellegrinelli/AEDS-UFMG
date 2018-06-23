/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018
*/

/*
	Nesse código teremos a definição de todos os métodos/funções responsáveis
	por esconder uma mensagem já criptografada em um aquivo PPM (ASCII, P3)
*/

struct Image hide_message_in_image(struct Image original_image, long *encoded_message, int block_count, int rsa_n, char delimiter);

long * recover_message_from_image(struct Image image, char delimiter, int *block_count, int rsa_n);

char* integer_to_binary_string(int n, int str_size);

int binary_string_to_int(char *b);
