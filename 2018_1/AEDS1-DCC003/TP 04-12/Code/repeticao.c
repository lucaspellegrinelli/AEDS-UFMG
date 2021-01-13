#include <stdio.h>
#include <string.h>

int main(void) {
  int valores[10];
  int valorRepetido = -1;

  for(int i = 0; i < 10; i++) valores[i] = -1;

  for(int i = 0; i < 10; i++){
    int n;
    scanf("%d", &n);

    for(int j = 0; j < 10; j++){
      if(valores[j] == n){
        valorRepetido = n;
        break;
      }
    }

    valores[i] = n;

    if(valorRepetido != -1) break;
  }

  if(valorRepetido != -1)
    printf("%d\n", valorRepetido);
  else
    printf("Nao ha repeticoes\n");

  return 0;
}
