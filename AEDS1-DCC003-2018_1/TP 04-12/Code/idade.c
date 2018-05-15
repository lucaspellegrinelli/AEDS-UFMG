#include <stdio.h>
#include <string.h>

int main(void) {
  int idades[5];
  char nomes[5][20];

  int idMaisVelha = -1;
  int idadeMaisVelha = -1;
  int idMaisNova = -1;
  int idadeMaisNova = 999;

  for (int i = 0; i < 5; i++){
    printf("Nome: ");
    scanf("%s", nomes[i]);
    printf("Idade: ");
    scanf("%i", &idades[i]);

    if(idades[i] < idadeMaisNova){
      idadeMaisNova = idades[i];
      idMaisNova = i;
    }

    if(idades[i] > idadeMaisVelha){
      idadeMaisVelha = idades[i];
      idMaisVelha = i;
    }
  }

  printf("Pessoa mais nova: %s\n", nomes[idMaisNova]);
  printf("Pessoa mais velha: %s\n", nomes[idMaisVelha]);

  return 0;
}
