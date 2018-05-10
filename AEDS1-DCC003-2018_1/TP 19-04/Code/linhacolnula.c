#include <stdio.h>

#define ROWS 4
#define COLS 4

int main(void) {
  int matrix[ROWS][COLS];

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      scanf("%d", &matrix[i][j]);
    }
  }

  int rowNullCount = 0;
  int rowNull = 1;

  int colNullCount = 0;
  int colNull[ROWS];
  for(int i = 0; i < COLS; i++) colNull[i] = 0;

  for(int i = 0; i < ROWS; i++){
    rowNull = 1;
    for(int j = 0; j < COLS; j++){
      if(matrix[i][j] != 0){
        rowNull = 0;
        colNull[j] = 1;
      }
    }
    if(rowNull) rowNullCount++;
  }

  for(int i = 0; i < COLS; i++)
    if(!colNull[i]) colNullCount++;

  printf("Total de colunas nulas: %d\n", colNullCount);
  printf("Total de linhas nulas: %d\n", rowNullCount);

  return 0;
}
