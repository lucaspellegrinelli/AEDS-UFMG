/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018
*/

/*
	Nesse código teremos a definição de todos os métodos/funções responsáveis
	por esconder uma mensagem já criptografada em um aquivo PPM (ASCII, P3)
*/

/*
  Esconde os bits dos blocos de mensagem nos componentes RGB dos pixels da imagem informada

  Entrada:
  'original_image' -> Os dados da imagem original no formato struct Image
  'encoded_message' -> A mensagem já criptografada e quebrada em blocos
  'block_count' -> Número de blocos em que a mensagem foi quebrada
  'rsa_n' -> O valor de 'n' calculado no RSA
  'delimiter' -> Delimitador

  Saída:
  'return' -> Novo struct Image similar a 'original_image' porém já com os bits de 'encoded_message' escondidos
*/
struct Image hide_message_in_image(struct Image original_image, long *encoded_message, int block_count, int rsa_n, char delimiter);

/*
  Recupera os blocos de mensagem cifrados a partir de uma imagem com os blocos escondidos

  Entrada:
  'image' -> Os dados da imagem que contém os blocos escondidos
  'delimiter' -> Delimitador
  'block_count' -> Número de blocos
  'rsa_n' -> O valor de 'n' calculado no RSA

  Saída:
  'return' -> Os blocos de mensagem criptografados
*/
long * recover_message_from_image(struct Image image, char delimiter, int *block_count, int rsa_n);

/*
  Transforma um inteiro em uma string com sua representação binária

  Entrada:
  'n' -> Número a ser transformado em binário
  'str_size' -> Tamanho da string que será criada e retornada

  Saída:
  'return' -> A string com a representação binária de 'n'
*/
char* integer_to_binary_string(int n, int str_size);

/*
  Transforma uma string com a representação binária de um inteiro no respectivo inteiro

  Entrada:
  'b' -> String com a representação binária de um inteiro

  Saída:
  'return' -> O inteiro cuja representação binária é 'b'
*/
int binary_string_to_int(char *b);
