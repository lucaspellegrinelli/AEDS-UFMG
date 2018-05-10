#include <stdio.h>
#include <math.h>

int inverter(int n);

int main(void) {
  int n1 = 10;
  int n2 = 9899;
  int n3 = 1723;

  printf("0%i\n", inverter(n1));
  printf("%i\n", inverter(n2));
  printf("%i", inverter(n3));
}

int inverter(int n){
  int result = 0;
  for(int i = 1; i <= 4; i++){
    int mult = pow(10, i);
    result += (10 * (n % mult) / mult) * (10000 / mult);
  }

  return result;
}
