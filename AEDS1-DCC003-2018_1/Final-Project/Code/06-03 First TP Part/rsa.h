/*
  Autor: Lucas Pellegrinelli
  Data: 19/05/2018
*/

/*
  Nesse código temos a definição de todos os métodos que serão utilizados
  no processo de criptografar/descriptografar mensagens.
*/

/*
  Gera as variáveis 'n', 'd' e 'e' (variáveis que vão ser usadas no algoritmo
  RSA) a partir das variáveis 'p' e 'q' dadas pelo usuário.

  Entradas:
  'p' -> Primeiro número primo informado
  'q' -> Segundo número primo informado

  Saída:
  'n' -> Resultado da multiplicação entre 'p' e 'q'
  'e' -> Número entre 1 e (p-1)*(q-1) tal que 'e' e (p-1)*(q-1) sejam co-primos
  'd' -> Inverso nodular multiplicativo de 'e'
*/
void choose_variables(long p, long q, long *n, long *d, long *e);

/*
  Criptografa os blocos de mensagem

  Entradas:
  'message_blocks' -> A mensagem já quebrada em blocos de tamanhos menores que 'n'
  'block_count' -> Número de blocos
  'n' -> Variável calculada no método 'choose_variables' utilizada na cifragem
  'e' -> Variável calculada no método 'choose_variables'  utilizada na cifragem

  Saída:
  'return' -> Vetor de blocos com a mensagem já criptografada
*/
long * encode_message(long *message_blocks, int block_count, long n, long e);

/*
  Descriptografa os blocos de mensagem

  Entradas:
  'encoded_blocks' -> Os blocos contendo a mensagem já criptografada
  'block_count' -> Número de blocos
  'n' -> Variável calculada no método 'choose_variables' utilizada na decifragem
  'd' -> Variável calculada no método 'choose_variables'  utilizada na decifragem

  Saída:
  'return' -> Vetor de blocos com a mensagem já descriptografada
*/
long * decode_message(long *encoded_blocks, int block_count, long n, long d);

/*
  Quebra a mensagem original em blocos de tamanho menor que 'n'

  Entrada:
  'message' -> Texto contendo a mensagem a ser cifrada
  'n' -> Variável calculada no método 'choose_variables'

  Saída:
  'block_count' -> Variável onde será atribuido o número de blocos gerados
  'return' -> Blocos gerados após a quebra da mensagem
*/
long * break_message_into_blocks(char message[], long n, int *block_count);

/*
  Junta os blocos já descriptografados para gerar a mensagem original

  Entrada:
  'decoded_blocks' -> Os blocos contendo a mensagem já decifrada
  'block_count' -> Número de blocos
  'n' -> Variável calculada no método 'choose_variables'

  Saída:
  'return' -> Texto contendo a mensagem contida nos blocos recebidos
*/
char * build_message_from_blocks(long *decoded_blocks, int block_count, long n);

/*
  Gera uma string contendo todos os valores ASCII de cada caractere em sequência

  Entrada:
  'message' -> A string contendo a mensagem

  Saída:
  'return' -> A string contendo os valores ASCII de cada um dos caracteres da mensagem
*/
char * generate_full_message_string(char message[]);

/*
  Gera uma string juntando todos os valores ASCII de todos os blocos de blocos
  já descriptografados

  Entrada:
  'blocks' -> Os blocos de mensagem já descriptografados
  'block_len' -> Número de blocos
  'n' -> Variável calculada no método 'choose_variables'

  Saída:
  'return' -> Uma string contendo todos os valores ASCII de todos os caracteres
  da mensagem original, que foram recebidos pela função em blocos.
*/
char * recover_full_message_string(long *blocks, int block_len, long n);

/*
  Transforma um número em uma string contendo os dígitos do valor ASCII relacionado
  ao caractere relacionado com o número recebido

  Entrada:
  'n' -> Um número relacionado a um caractere

  Saída:
  'return' -> String contendo cada dígito do valor ASCII do caractere relacionado
  com o número recebido
*/
char * encode_char(long n);

/*
  Transforma uma string contendo cada dígito de um valor ASCII de um caractere
  no valor relacionado ao caractere em questão

  Entrada:
  'c' -> String contendo os dígitos do valor ASCII

  Saída:
  'return' -> Número ASCII relacionado ao caractere de valores ASCII recebidos
  pela função
*/
long decode_char(char *c);

/*
  Implementação do algoritmo de Exponenciação Modular

  PS. Não deve ser a implementação mais eficiente dito que não peguei o código
  de lugar nenhum, mas cumpre o propósito.

  Entrada:
  'a' -> Base
  'b' -> Expoente
  'm' -> Modulo

  Saída:
  'return' -> a^b mod m
*/
long power_mod(long a, long b, long m);

/*
  Calcula o inverso multiplicativo de dois números

  Entrada:
  'a' -> Primeiro número
  'b' -> Segundo número

  Saída:
  'return' -> Inverso multiplicativo entre 'a' e 'b'
*/
long mul_inv(long a, long b);

/*
  Retorna o maior divisor comum entre dois números

  Entrada:
  'a' -> Primeiro número
  'b' -> Segundo número

  Saída:
  'return' -> Maior divisor comum entre 'a' e 'b'
*/
long greatest_common_divisor(long a, long b);

/*
  Concatena um caractere ao final de uma string

  Entrada:
  's1' -> A string que o caractere será concatenado
  'c' -> O caractere a ser concatenado

  Saída:
  'return' -> A string 's' com o caractere 'c' no final
*/
char * concat_char(const char *s, const char c);
