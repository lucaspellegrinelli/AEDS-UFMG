#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "PPMIO.h"

char* integer_to_binary_string(int n){
  int number_of_bits = sizeof(int) * 8;
  char *binary = malloc(number_of_bits);

  for (int i = number_of_bits - 1; i >= 0; i--){
    binary[i] = ((1 & n) == 1) ? '1' : '0';
    n >>= 1;
  }

  return binary;
}

int main(void){
  int a = 0;

  if(a == 0){
    struct Image image_write;

    image_write.width = 100;
    image_write.height = 100;

    image_write.pixels = (int**) malloc(sizeof(int *) * image_write.width * image_write.height);

    for(int i = 0; i < image_write.width * image_write.height; i++){
      image_write.pixels[i] = malloc(sizeof(int) * 3);
      image_write.pixels[i][0] = i % 256;
      image_write.pixels[i][1] = abs(i - 127) % 256;
      image_write.pixels[i][2] = abs(i + 127) % 256;
    }

    write_image(image_write, "file.ppm");
  }else if(a == 1){
    struct Image image = read_image("file.ppm");

    for(int i = 0; i < image.width; i++){
      for(int j = 0; j < image.height; j++){
        printf("%d %d %d\n", image.pixels[j + i * image.width][0],
                             image.pixels[j + i * image.width][1],
                             image.pixels[j + i * image.width][2]);
      }
    }
  }

  return 0;
}
