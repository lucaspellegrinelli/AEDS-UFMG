#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "steganography.h"
#include "PPMIO.h"
#include "rsa.h"

struct Image hide_message_in_image(struct Image original_image, long *encoded_message, int block_count, int rsa_n, char delimiter){
  int pixel_counter = 0;
  int rgb_component_counter = 0;

  int max_block_size_binary = log(rsa_n) / log(2) + 1;

  for(int i = 0; i < block_count; i++){
    char *block_as_binary = integer_to_binary_string((int)encoded_message[i], max_block_size_binary);

    for(int i = 0; i < max_block_size_binary; i++){
      char current_bit = block_as_binary[i];
      long current_rgb_comp_as_binary = as_other_base(original_image.pixels[pixel_counter][rgb_component_counter], 10, 2);

      if(current_rgb_comp_as_binary % 10 == 0 && current_bit == '1')
        original_image.pixels[pixel_counter][rgb_component_counter] += 1;
      else if(current_rgb_comp_as_binary % 10 == 1 && current_bit == '0')
        original_image.pixels[pixel_counter][rgb_component_counter] -= 1;

      rgb_component_counter++;
      if(rgb_component_counter > 2){
        rgb_component_counter = 0;
        pixel_counter++;
      }
    }
  }

  /*
   Linha só com 1's para indicar a parada.

   Porque dá certo?

   O motivo pelo qual isso poderia dar errado seria caso um bloco que não fosse
   o último fosse todo cheio de 1s, fazendo o decodificador parar de ler antes
   de ter lido todos os blocos. Porém para isso acontecer, como cada bloco é
   limitado ao valor de N (bloco é mod N), então para que a representação binária
   de um bloco fosse composta somente por 1s, então N teria que ser 2^x para qualquer
   x, assim os blocos podem ter valor ((2^x) - 1) e assim ter só 1s na representação
   binária. Mas visto que 2^x é uma potência de 2, só é possível obter valores desse tipo
   pela multiplicação de outras potências de 2, mas dito que N é um produto entre
   dois números primos e o único primo que é potência de 2 é o próprio 2, é impossível
   obter um número no formato 2^x para N (já que só temos um primo que é potência de 2
   e precisaríamos de pelo menos dois deles para formar 2^x), sendo assim impossível de
   acontecer um bloco com representação binária toda igual a 1.

  */
  for(int i = 0; i < max_block_size_binary; i++){
    long current_rgb_comp_as_binary = as_other_base(original_image.pixels[pixel_counter][rgb_component_counter], 10, 2);
    if(current_rgb_comp_as_binary % 10 == 0)
      original_image.pixels[pixel_counter][rgb_component_counter] += 1;

    rgb_component_counter++;
    if(rgb_component_counter > 2){
      rgb_component_counter = 0;
      pixel_counter++;
    }
  }

  return original_image;
}

long * recover_message_from_image(struct Image image, char delimiter, int *block_count, int rsa_n){
  int max_block_size_binary = log(rsa_n) / log(2) + 1;

  // Cada pixel pode armazenar 3 bits e cada bloco tem 32 bits
  int max_number_of_blocks_hidden = (3.0 * image.width * image.height) / max_block_size_binary;
  long *message_blocks = malloc(sizeof(long) * max_number_of_blocks_hidden);
  int message_blocks_index = 0;

  char *current_block_buffer = malloc(sizeof(char) * max_block_size_binary);
  int current_block_int = 0;

  for(int i = 0; i < image.width; i++){
    for(int j = 0; j < image.height; j++){
      for(int rgb = 0; rgb < 3; rgb++){
        int rgb_component_value_as_binary = as_other_base(image.pixels[i * image.width + j][rgb], 10, 2);
        int least_significant_bit_value = rgb_component_value_as_binary % 10;
        current_block_buffer[current_block_int] = least_significant_bit_value == 1 ? '1' : '0';

        current_block_int++;
        if(current_block_int >= max_block_size_binary){
          current_block_int = 0;
          int block_value = binary_string_to_int(current_block_buffer);

          if(block_value == pow(2, max_block_size_binary) - 1) return message_blocks; // Linha de parada, tudo 1

          message_blocks[message_blocks_index++] = block_value;
          *block_count = *block_count + 1;
          for(int i = 0; i < max_block_size_binary; i++) current_block_buffer[i] = '\0';
        }
      }
    }
  }

  return message_blocks;
}

char* integer_to_binary_string(int n, int str_size){
  char *binary = malloc(str_size);

  for (int i = str_size - 1; i >= 0; i--){
    binary[i] = ((1 & n) == 1) ? '1' : '0';
    n >>= 1;
  }

  return binary;
}

int binary_string_to_int(char *b){
  return (int) strtol(b, NULL, 2);
}
