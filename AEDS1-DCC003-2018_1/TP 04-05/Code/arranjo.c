#include <stdio.h>
#include <math.h>

int fatorial(int n);

int main(void) {
  int n;
  int r;

  scanf("%d", &n);
  scanf("%d", &r);

  if(n <= 0) printf("n invalido!\n");
  else if(r <= 0) printf("r invalido!\n");
  else if(r > n) printf("r nao pode ser maior do que n!\n");
  else printf("%d\n", fatorial(n) / fatorial(n - r));

  return 0;
}

int fatorial(int n){
	if(n == 0 || n == 1){
		return 1;
	}else{
		return fatorial(n - 1) * n;
	}
}
