#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "PPMIO.h"

#define HEADER_MAX_LINES 10
#define HEADER_LINE_LENGTH 1000
#define STANDARD_HEADER_LINES 3
#define STANDARD_DIMENSION_INDEX 1
#define RGB_NUMBER_COMPONENTS 3

struct Image read_image(char *path){
  struct Image output;

  const char* open_mode = "r";
  FILE *image_file = fopen(path, open_mode);

  if (image_file == NULL){
      printf("Não foi possível abrir a imagem especificada.\n");
      exit(1);
  }

  int header_count = 0;
  int body_count = 0;
  int rgb_component_index = 0;
  int comment_lines = 0;

  char **header = (char **)malloc(sizeof(char *) * HEADER_MAX_LINES);

  char *buffer = NULL;
  size_t len = 0;
  ssize_t read;

  // Lê os headers do arquivo (tipo, tamanho, comentários...)
  while ((read = getline(&buffer, &len, image_file)) != -1) {
    if(header_count < comment_lines + STANDARD_HEADER_LINES){
      header[header_count] = malloc(sizeof(char) * HEADER_LINE_LENGTH);
      if(buffer[0] == '#') comment_lines++; // Suporte para comentários
      strcpy(header[header_count++], buffer); // Copia a linha atual para a header
    }else break;
  }

  char *splitted_dimensions = strtok(header[STANDARD_DIMENSION_INDEX + comment_lines], " "); // Divide o texto com as dimensões
  output.width = atoi(splitted_dimensions); // Coloca a largura
  splitted_dimensions = strtok(NULL, " \t"); // Pula para a altura
  output.height = atoi(splitted_dimensions); // Coloca a altura

  int **body = (int **)malloc(sizeof(int *) * output.width * output.height);
  body[0] = malloc(sizeof(int) * RGB_NUMBER_COMPONENTS);

  do{ // Do .. While pois temos a primeira linha da imagem como resto no buffer de quando pegamos a header
    int buffer_size = 0;
    for(int i = 0; i < strlen(buffer); i++){
      if(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\r' || buffer[i] == '\n' || buffer[i] == '\v' || buffer[i] == '\f')
        buffer_size++;
    }

    char delimit[6] = " \t\r\n\v\f";

    char *rgb_components = strtok(buffer, delimit);

    while(rgb_components != NULL){
      body[body_count][rgb_component_index] = atoi(rgb_components);

      rgb_component_index++;
      if(rgb_component_index > 2){
        rgb_component_index = 0;
        body_count++;
        body[body_count] = malloc(sizeof(int) * RGB_NUMBER_COMPONENTS);
      }

      rgb_components = strtok(NULL, delimit);
    }
  }while ((read = getline(&buffer, &len, image_file)) != -1);

  output.header = header;
  output.pixels = body;

  return output;
}

void write_image(struct Image image, char *output_name){
  FILE *fp = fopen(output_name, "wb");
  fprintf(fp, "P3\n%d %d\n255\n", image.height, image.width);

  for(int i = 0; i < image.height; i++){
    for(int j = 0; j < image.width; j++){
      fprintf(fp, "%d\n%d\n%d\n", image.pixels[j + i * image.height][0],
                            image.pixels[j + i * image.height][1],
                            image.pixels[j + i * image.height][2]);
    }

    fprintf(fp, "\n");
  }

  fclose(fp);
}
