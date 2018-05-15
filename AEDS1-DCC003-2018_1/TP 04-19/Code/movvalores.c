#include <stdio.h>

#define ROWS 4
#define COLS 4

int main(void) {
  int matrix[ROWS][COLS];

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      scanf("%d", &matrix[(i + 1) % ROWS][(j + 1) % COLS]);
    }
  }

  for (int i = 0; i < ROWS; i++){
    for (int j = 0; j < COLS; j++){
      printf("%d\t", matrix[i][j]);
    }

    printf("\n");
  }

  return 0;
}
