/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018
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
  'd' -> Inverso modular multiplicativo de 'e'
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
char * generate_full_message_string(char message[], int encoding_base);

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
  Gera os blocos de mensagem criptografadas a partir da string recebida

  Entrada:
  'encoded_message' -> String contendo os blocos de mensagem cifradas separadas
  por '/'

  Saída:
  'block_count' -> Número de blocos
  'return' -> Os blocos gerados a partir da string fornecida
*/
long * get_blocks_from_string(char *encoded_message, int *block_count);

char * encode_char(long n, int base);

long decode_char(char *n, int base);

/*
  Escolhe em qual base numérica o código irá trabalhar:

  Se n > 10, então a base escolhida será a 10.
  Se n <= 10, então a base escolhida será a n-1

  OBS. A base 10 não deve ser utilizada para 'n' <= 10 já que como ASCII trabalha
  com números na base decimal, um número pode ser por exemplo '97', sendo
  impossível dividir esse número em blocos com valores menores que 'n' (para
  um 'n' = 6 por exemplo, ambos '9' e '7' são maiores), comprometendo a criptografia.
  Dessa forma é necessário converter para uma base menor para garantir que todos os
  dígitos serão menores que 'n'.

  Entrada:
  'n' -> Variável calculada no método 'choose_variables'

  Saída:
  'return' -> Base numérica escolhida
*/
int choose_encoding_base(long n);

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
  Converte um número de um base específica para outra

  Entrada:
  'n' -> Número a ser convertido
  'n_base' -> Base em que n está escrito
  'to_base' -> Base em que n será convertido

  Saída:
  'return' -> Número convertido para a nova base
*/
long as_other_base(long n, int n_base, int to_base);

/*
  Converte um número em uma string contendo seus dígitos

  Entrada:
  'n' -> Número a ser convertido

  Saída:
  'return' -> String contendo os dígitos do número
*/
char * long_to_char(long n);

/*
  Converte uma string em um número com os dígitos contidos na string

  Entrada:
  'c' -> A string a ser convertida

  Saída:
  'return' -> O número gerado pela conversão da string
*/
long char_to_long(char *c);

/*
  Concatena um caractere ao final de uma string

  Entrada:
  's1' -> A string que o caractere será concatenado
  'c' -> O caractere a ser concatenado

  Saída:
  'return' -> A string 's' com o caractere 'c' no final
*/
char * concat_char(const char *s, const char c);
