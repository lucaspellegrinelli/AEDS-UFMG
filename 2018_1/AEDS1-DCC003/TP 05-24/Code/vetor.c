#include <stdio.h>
#include <stdlib.h>

int main(){
  int N;
  int M;

  scanf("%d", &N);
  scanf("%d", &M);

  int *vetA = malloc(N * sizeof(int));
  int *vetB = malloc(M * sizeof(int));

  for(int i = 0; i < N; i++){
    scanf("%d", &vetA[i]);
  }

  for(int i = 0; i < M; i++){
    scanf("%d", &vetB[i]);
  }

  int maxSize = N;
  if(N < M)
    maxSize = M;

  int *vetSum = malloc(maxSize * sizeof(int));

  for(int i = 0; i < maxSize; i++){
    if(i < N && i < M){
      vetSum[i] = vetA[i] + vetB[i];
    }else{
      if(maxSize == N)
        vetSum[i] = vetA[i];
      else
        vetSum[i] = vetB[i];
    }
  }

  for(int i = 0; i < maxSize; i++){
    printf("%d\n", vetSum[i]);
  }

  return 0;
}
