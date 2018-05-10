#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool ePrimo(int n);

int main(void) {
  int numeroPrimos = 0;

  for(;;){
  	int n;
  	scanf("%d", &n);

  	if(n >= 0){
  		if(ePrimo(n))
  			numeroPrimos++;
  	}else{
  		break;
  	}
  }

  printf("Foram identificados %d numeros primos\n", numeroPrimos);

  return 0;
}

bool ePrimo(int n){
	if(n == 2) return true;
	if(n % 2 == 0 || n < 2) return false;

	for(int i = 3; i <= sqrt(n); i += 2){
		if(n % i == 0) return false;
	}

	return true;
}
