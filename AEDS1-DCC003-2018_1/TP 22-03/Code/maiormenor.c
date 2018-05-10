#include <stdio.h>

int main(){
	int n[5];

	scanf("%d%d%d%d%d", &n[0], &n[1], &n[2], &n[3], &n[4]);

	int min = n[0];
	for(int i = 1; i < 5; i++){
		if(n[i] < min)
			min = n[i];
	}

	int max = n[0];
	for(int i = 1; i < 5; i++){
		if(n[i] > max)
			max = n[i];
	}

	int count = 0;
	for(int i = 0; i < 5; i++){
		if(n[i] % 3 == 0)
			count++;
	}

	printf("Maior: %d\n", max);
	printf("Menor: %d\n", min);
	printf("Divisiveis por 3: %d\n", count);

	return 0;
}
