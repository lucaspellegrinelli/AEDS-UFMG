#include <stdio.h>

int obter_conceito(int n1, int n2, int n3, int n4, char *conceito);

int main(){
	float n1, n2, n3, n4;
	char conceito;

	scanf("%f", &n1);
	scanf("%f", &n2);
	scanf("%f", &n3);
	scanf("%f", &n4);

	int sucesso = obter_conceito(n1, n2, n3, n4, &conceito);

	if(sucesso == 0){
		printf("Nota invalida!\n");
	}else{
		printf("Conceito: %c\n", conceito);
	}

	return 0;
}

int obter_conceito(int n1, int n2, int n3, int n4, char *conceito){
	if(n1 < 0 || n1 > 100 || n2 < 0 || n2 > 100 || n3 < 0 || n3 > 100 || n4 < 0 || n4 > 100){
		return 0;
	}

	float media = (n1 + n2 + n3 + n4) / 4.0;

	if(media >= 90 && media <= 100)
		*conceito = 'A';
	else if(media < 90 && media >= 80)
		*conceito = 'B';
	else if(media < 80 && media >= 70)
		*conceito = 'C';
	else if(media < 70 && media >= 50)
		*conceito = 'D';
	else if(media < 50 && media >= 40)
		*conceito = 'E';
	else
		*conceito = 'F';

	return 1;
}
