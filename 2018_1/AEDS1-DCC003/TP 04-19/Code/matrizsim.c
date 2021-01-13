#include <stdio.h>

#define ROWS 4
#define COLS 4

int main(void) {
  int matrix[ROWS][COLS];
  int equal = 1;

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      scanf("%d", &matrix[i][j]);
    }
  }

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      if(matrix[i][j] != matrix[j][i]) equal = 0;
    }
  }

  if(equal)
    printf("Matriz simetrica");
  else
    printf("Nao e uma matriz simetrica");

  return 0;
}
