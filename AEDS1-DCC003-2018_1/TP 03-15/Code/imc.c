#include <stdio.h>

float calcIMC(float altura, float peso);

int main(void) {
  float alturaBrutus = 1.84;
  float pesoBrutus = 122;
  float alturaOlivia = 1.76;
  float pesoOlivia = 45;

  float imcBrutus = calcIMC(alturaBrutus, pesoBrutus);
  float imcOlivia = calcIMC(alturaOlivia, pesoOlivia);

  printf("IMC Brutus = %.2f\n", imcBrutus);
  printf("IMC Olivia = %.2f\n", imcOlivia);

  float pesoBrutusIdeal = 24.999999 * alturaBrutus * alturaBrutus;
  float pesoOliviaIdeal = 18.5 * alturaOlivia * alturaOlivia;

  printf("Brutus precisa perder %.2f quilos\n", pesoBrutus - pesoBrutusIdeal);

  printf("Olivia precisa ganhar %.2f quilos", pesoOliviaIdeal - pesoOlivia);

  return 0;
}

float calcIMC(float altura, float peso){
  return peso / (altura * altura);
}
