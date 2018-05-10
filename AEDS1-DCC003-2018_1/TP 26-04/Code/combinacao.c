#include <stdio.h>

int fatorial(int v);
int combinacao(int n, int p, int *cnp);

int main(){
	int n, p, c;

	scanf("%d", &n);
	scanf("%d", &p);

	int sucesso = combinacao(n, p, &c);

	if(sucesso == 0){
		printf("Parametro invalido!\n");
	}else{
		printf("Combinacao: %d\n", c);
	}

	return 0;
}

int fatoral(int v){
	if(v <= 1) return 1;
	else return fatoral(v - 1) * v;
}

int combinacao(int n, int p, int *cnp){
	if(n < 0 || p < 0 || n < p) return 0;
	*cnp = fatoral(n) / (fatoral(p) * fatoral(n - p));
	return 1;
}
