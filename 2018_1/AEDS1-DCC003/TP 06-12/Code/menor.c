#include <stdio.h>
#include <stdlib.h>

int menor(int *v, int n);

int main(){
  int n;
  scanf("%d", &n);
  int v[n];
  for(int i = 0; i < n; i++){
    scanf("%d", &v[i]);
  }

  int m = menor(v, n - 1);

  printf("%d\n", m);
}

int menor(int *v, int n){
  if(n == 0) return v[0];
  else{
    if(v[n] < menor(v, n - 1)) return v[n];
    else return menor(v, n - 1);
  }
}
