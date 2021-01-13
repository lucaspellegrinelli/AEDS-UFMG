#include <stdio.h>
#include <string.h>

int main(void) {
  int impares[10];
  int pares[10];

  for(int i = 0; i < 10; i++){
    int n;
    scanf("%d", &n);
    if(n % 2 == 0){
      impares[i] = -1;
      pares[i] = n;
    }else{
      impares[i] = n;
      pares[i] = -1;
    }
  }

  printf("Valores impares:\n");
  for(int i = 0; i < 10; i++){
    if(impares[i] != -1)
      printf("%d\n", impares[i]);
  }

  printf("Valores pares:\n");
  for(int i = 0; i < 10; i++){
    if(pares[i] != -1)
      printf("%d\n", pares[i]);
  }

  return 0;
}
