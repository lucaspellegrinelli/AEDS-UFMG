#include <stdio.h>

int main(void) {
  int a1, r, n;

  scanf("%d", &a1);
  scanf("%d", &r);
  scanf("%d", &n);

  for(int i = 0; i < n; i++){
  	printf("%d\n", a1 + r * i);
  }

  return 0;
}
