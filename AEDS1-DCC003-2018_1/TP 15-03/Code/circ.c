#include <stdio.h>

#define PI 3.1416

float perimetro(float r);
float area(float r);
float volume(float r);

int main(void) {
  float r1 = 1.0;
  float r2 = 2.5;
  float r3 = 5.2;

  printf("P=%.2f\tA=%.2f\tV=%.2f\n", perimetro(r1), area(r1), volume(r1));
  printf("P=%.2f\tA=%.2f\tV=%.2f\n", perimetro(r2), area(r2), volume(r2));
  printf("P=%.2f\tA=%.2f\tV=%.2f", perimetro(r3), area(r3), volume(r3));
}

float perimetro(float r){
  return 2 * PI * r;
}

float area(float r){
  return PI * r * r;
}

float volume(float r){
  return (4 * PI * r * r * r) / 3;
}
