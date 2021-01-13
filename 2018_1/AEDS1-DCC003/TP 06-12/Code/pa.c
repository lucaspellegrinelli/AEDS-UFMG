#include <stdio.h>
#include <stdlib.h>

void imprimirPA(int r, int x, int n);

int main(){
  int r;
  int x;
  int n;

  scanf("%d%d%d", &r, &x, &n);

  imprimirPA(r, x, n);
}

void imprimirPA(int r, int x, int n){
  if(n == 1){
    printf("%d\n", x);
  }else{
    imprimirPA(r, x + r, n - 1);
    printf("%d\n", x);
  }
}
