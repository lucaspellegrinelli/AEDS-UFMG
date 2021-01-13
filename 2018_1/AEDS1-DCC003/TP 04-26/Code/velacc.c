#include <stdio.h>

float velocidade_final(float v, float a, float t);
float distancia(float v, float a, float t);

int main(){
	float a, v, t;

	scanf("%f", &v);
	scanf("%f", &a);
	scanf("%f", &t);

	printf("Velocidade final: %.2f\n", velocidade_final(v, a, t));

	printf("Distancia percorrida: %.2f\n", distancia(v, a, t));

	return 0;
}

float velocidade_final(float v, float a, float t){
	return v + a * t;
}

float distancia(float v, float a, float t){
	return v * t + (a * t * t) / 2;
}
