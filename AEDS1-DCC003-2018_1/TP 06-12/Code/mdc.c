#include <stdio.h>
#include <stdlib.h>

int divisores(int a, int b, int n, int *mdc);
int contarFatores(int n);

int main(){
  int a;
  int b;
  int mdc;

  scanf("%d%d", &a, &b);

  int n = divisores(a, b, 1, &mdc);

  printf("%d %d\n", mdc, n);
}

int divisores(int a, int b, int n, int *mdc){
  if (a == 0){
    *mdc = b;
    return contarFatores(b);
  }else{
    if(a > 0){
      int a_ = a;
      a = b % a;
      b = a_;
    }

    divisores(a, b, n + 1, mdc);
  }
}

int contarFatores(int n){
  int f = 1;
  if(n == 1) return 1;
  else{
    for(int i = 2; i <= (n / 2); i++){
      if(n % i == 0) f++;
    }
    return (f + 1);
  }
}
