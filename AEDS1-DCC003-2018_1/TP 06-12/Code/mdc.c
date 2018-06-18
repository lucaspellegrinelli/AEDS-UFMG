#include <stdio.h>
#include <stdlib.h>

int divisores(int a, int b, int n, int *mdc);
int min(int a, int b);

int main(){
  int a;
  int b;
  int mdc;

  scanf("%d%d", &a, &b);

  int n = divisores(a, b, -1, &mdc);

  printf("%d %d\n", mdc, n);
}

int divisores(int a, int b, int n, int *mdc){
  if(n == -1){
    if (a == 0){
      int _b = *mdc;
      *mdc = b;
      return divisores(b, _b, min(b, _b), mdc);
    }else{
      *mdc = b;
      int _a = a;
      a = b % a;
      b = _a;
    }

    divisores(a, b, n, mdc);
  }else if(n > -1){
    if(n > 0){
      if(a % n == 0 & b % n == 0){
        return divisores(a, b, n - 1, mdc);
      }else{
        return divisores(a, b, n - 1, mdc) - 1;
      }
    }else{
      return min(a, b);
    }
  }
}

int min(int a, int b){
  if(a < b) return a;
  else return b;
}
