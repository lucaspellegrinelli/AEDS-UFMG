#include <stdio.h>
#include <stdlib.h>

struct Ponto{
  float x;
  float y;
};

struct Retangulo{
  struct Ponto upRight;
  struct Ponto downLeft;
};

float calcArea(struct Retangulo rect);
int isIn(struct Retangulo rect, struct Ponto point);

int main(){
  int N;
  scanf("%d", &N);

  struct Retangulo rects[N];

  for(int i = 0; i < N; i++){
    scanf("%f", &rects[i].upRight.x);
    scanf("%f", &rects[i].upRight.y);
    scanf("%f", &rects[i].downLeft.x);
    scanf("%f", &rects[i].downLeft.y);
  }

  for(int i = 0; i < N; i++){
    printf("Area do retangulo %d: %.2f\n", i, calcArea(rects[i]));
  }

  int M;
  scanf("%d", &M);

  struct Ponto points[M];

  for(int i = 0; i < M; i++){
    scanf("%f", &points[i].x);
    scanf("%f", &points[i].y);
  }

  for(int i = 0; i < M; i++){
    if(isIn(rects[N - 1], points[i]) == 1){
      printf("O ponto %d esta dentro do retangulo %d\n", i, N - 1);
    }else{
      printf("O ponto %d nao esta dentro do retangulo %d\n", i, N - 1);
    }
  }

  return 0;
}

float calcArea(struct Retangulo rect){
  return (rect.upRight.x - rect.downLeft.x) * (rect.upRight.y - rect.downLeft.y);
}

int isIn(struct Retangulo rect, struct Ponto point){
  return (point.x >= rect.downLeft.x) && (point.x <= rect.upRight.x) &&
         (point.y >= rect.downLeft.y) && (point.y <= rect.upRight.y);
}
