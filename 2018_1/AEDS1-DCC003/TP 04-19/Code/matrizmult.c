#include <stdio.h>

#define ROWS 3
#define COLS 3

int main(void) {
  int matrix[ROWS][COLS];

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      scanf("%d", &matrix[i][j]);
    }
  }

  int cellVal;

  for (int i = 0; i < ROWS; i++){
    for (int j = 0; j < COLS; j++){
      cellVal = 0;
      for(int k = 0; k < COLS; k++){
        cellVal += matrix[i][k] * matrix[j][k];
      }

      printf("%d\t", cellVal);
    }
    printf("\n");
  }

  return 0;
}
