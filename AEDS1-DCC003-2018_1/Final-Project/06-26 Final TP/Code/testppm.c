#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 // so ta escrevendo o vermelho
void write(int **a, int size){
  FILE *fp = fopen("file.ppm", "wb");
  fprintf(fp, "P6\n%d %d\n255\n", 30, 30);

  for(int i = 0; i < size; i++){
    fwrite(a[i], 1, 3, fp);
  }

  fclose(fp);
}

int main(void){
  int **a = (int**) malloc(sizeof(int *) * 900);

  for(int i = 0; i < 900; i++){
    a[i] = malloc(sizeof(int) * 3);
    a[i][0] = 50;
    a[i][1] = 0;
    a[i][2] = 0;
  }

  write(a, 900);

  return 0;
}