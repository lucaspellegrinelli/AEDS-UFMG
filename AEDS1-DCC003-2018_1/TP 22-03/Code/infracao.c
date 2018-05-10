#include <stdio.h>

int main(){
	float vel, velmax;
	scanf("%f%f", &velmax, &vel);

	float perc = (vel/velmax) * 100.0;

	if(vel >= 0 && velmax >= 0){
	if(vel <= velmax){
		printf("Nenhuma infracao cometida\n");
	}else{
		if(perc <= 120.0){
			printf("Infracao media\n");
		}else if(perc <= 150.0){
			printf("Infracao grave\n");
		}else{
			printf("Infracao gravissima\n");
		}
	}
	}else{
		printf("Velocidade invalida!\n");
	}

	return 0;
}
