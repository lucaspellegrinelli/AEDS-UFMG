#include <stdio.h>
#include <math.h>

int main(void) {

  int a, b;

  scanf("%d", &a);
  scanf("%d", &b);

  for(int i = a; i <= b; i++){
  	double raiz = sqrt(i);
  	if((int)raiz == raiz)
  		printf("%d\n", (int)i);
  }

  return 0;
}
