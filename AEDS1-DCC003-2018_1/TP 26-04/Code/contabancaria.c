#include <stdio.h>

void depositar(float d, float *saldo){
	*saldo += d;
}

int sacar(float d, float *saldo){
	if (*saldo > d){
		*saldo -= d;
		return 1;
	} else {
		return 0;
	}
}

int main(){
	float saldo, aux;

	printf("Saldo inicial: ");
	scanf("%f", &saldo);

	printf("Depositar: ");
	scanf("%f", &aux);

	depositar(aux, &saldo);

	printf("Sacar: ");
	scanf("%f", &aux);

	sacar(aux, &saldo);
	printf("Saldo %.2f\n", saldo);

	return 0;
}
