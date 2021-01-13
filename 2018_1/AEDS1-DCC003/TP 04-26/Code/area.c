#include <stdio.h>

#define PI 3.1415

float calcular_perimetro(float r);
float calcular_area(float r);
float calcular_volume(float r);

int main(){
	float r, v;

	printf("Raio: ");
	scanf("%f", &r);

	v = calcular_perimetro(r);
	printf("Perimetro: %.2f\n", v);

	v = calcular_area(r);
	printf("Area: %.2f\n", v);

	v = calcular_volume(r);
	printf("Volume: %.2f\n", v);

	return 0;
}

float calcular_perimetro(float r){
	return 2 * PI * r;
}

float calcular_area(float r){
	return PI * r * r;
}

float calcular_volume(float r){
	return (4 * PI * r * r * r) / 3;
}
