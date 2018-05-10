#include <stdio.h>

int main(){
	int soma1 = 0;
	int soma2 = 0;

	for(int i = 0; i < 9; i++){
		int digito;
		scanf("%d", &digito);
		soma1 += (10 - i) * digito;
		soma2 += (11 - i) * digito;
	}

	int d1 = (11 - (soma1 % 11)) % 10;

	soma2 += d1 * 2;
	int d2 = (11 - (soma2 % 11)) % 11;

	printf("Digitos verificadores: %d%d\n", d1, d2);
	return 0;
}
