#include <stdio.h>

int main(void) {
  float saldo = 789.54;
  saldo *= 1.0056;
  saldo += 303.2;
  saldo *= 1.0056;
  saldo -= 58.25;
  saldo *= 1.0056;

  printf("R$%.2f", saldo);
  return 0;
}
