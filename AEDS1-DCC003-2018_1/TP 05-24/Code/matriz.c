#include <stdio.h>
#include <stdlib.h>

void imprimir_matriz(int **m, int l, int c);

int main(){
  int mArows;
  int mAcols;
  int mBrows;
  int mBcols;

  scanf("%d", &mArows);
  scanf("%d", &mAcols);
  scanf("%d", &mBrows);
  scanf("%d", &mBcols);

  if(mAcols != mBrows){
    printf("Operacao invalida!\n");
    return 0;
  }

  int** mA = (int **) malloc(mArows * sizeof(int *));
  int** mB = (int **) malloc(mBrows * sizeof(int *));
  int** multAB = (int **) malloc(mArows * sizeof(int *));

  for(int i = 0; i < mArows; i++){
    mA[i] = malloc(mAcols * sizeof(int));
    for(int j = 0; j < mAcols; j++){
      scanf("%d", &mA[i][j]);
    }
  }

  for(int i = 0; i < mBrows; i++){
    mB[i] = malloc(mBcols * sizeof(int));
    for(int j = 0; j < mBcols; j++){
      scanf("%d", &mB[i][j]);
    }
  }

  for (int i = 0; i < mArows; i++){
    multAB[i] = malloc(mBcols * sizeof(int *));
    for (int j = 0; j < mBcols; j++){
      multAB[i][j] = 0;
      for(int k = 0; k < mBrows; k++){
        multAB[i][j] += mA[i][k] * mB[k][j];
      }
    }
  }

  imprimir_matriz(multAB, mArows, mBcols);

  return 0;
}

void imprimir_matriz(int **m, int l, int c){
  for (int i = 0; i < l; i++){
    for (int j = 0; j < c; j++){
      printf("%d\t", m[i][j]);
    }
    printf("\n");
  }
}
