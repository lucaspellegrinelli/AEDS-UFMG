#include <stdio.h>
#include <stdlib.h>

float somatorio(int n);

int main(){
  int n;
  scanf("%d", &n);

  float sum = somatorio(n);

  printf("%.2f\n", sum);
}

float somatorio(int n){
    if(n == 1) return 0.5;
    return ((float)n / (1.0 + (float)n)) + somatorio(n - 1);
}
