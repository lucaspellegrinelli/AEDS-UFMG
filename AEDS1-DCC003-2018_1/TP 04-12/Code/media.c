#include <stdio.h>
#include <math.h>

int main(void) {
  float media, desvio;
  int numeros[10];

  for(int i = 0; i < 10; i++){
    scanf("%d", &numeros[i]);
    media += numeros[i];
  }

  media /= 10.0;

  for(int i = 0; i < 10; i++){
    desvio += pow(numeros[i] - media, 2);
  }

  desvio *= 1.0/9.0;
  desvio = sqrt(desvio);

  printf("Media: %.2f\n", media);
  printf("Desvio padrao: %.2f\n", desvio);

  return 0;
}
