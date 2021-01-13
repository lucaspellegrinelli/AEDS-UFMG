#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_IRIS 6

struct Iris{
  float compr_sp;
  float larg_sp;
  float compr_pt;
  float larg_pt;
  char tipo[50];
};

void ler_iris(struct Iris *iris, int ler_tipo);
void cadastrar_iris(struct Iris *iris, int n);
float dist_euclid_iris(struct Iris a, struct Iris b);
char * classificar_iris(struct Iris incog, struct Iris *iris, int n);

int main(){
  struct Iris iris[NUM_IRIS];
  cadastrar_iris(iris, NUM_IRIS);

  struct Iris incog;
  ler_iris(&incog, 0);

  char *tipo = classificar_iris(incog, iris, NUM_IRIS);
  printf("Tipo de flor: %s\n", tipo);

  return 0;
}

void ler_iris(struct Iris *iris, int ler_tipo){
  scanf("%f", &iris->compr_sp);
  scanf("%f", &iris->larg_sp);
  scanf("%f", &iris->compr_pt);
  scanf("%f", &iris->larg_pt);
  if(ler_tipo == 1)
    scanf("%s", iris->tipo);
}

void cadastrar_iris(struct Iris *iris, int n){
  for(int i = 0; i < n; i++)
    ler_iris(&iris[i], 1);
}

float dist_euclid_iris(struct Iris a, struct Iris b){
  float dist_compr_sp = pow(a.compr_sp - b.compr_sp, 2);
  float dist_larg_sp = pow(a.larg_sp - b.larg_sp, 2);
  float dist_compr_pt = pow(a.compr_pt - b.compr_pt, 2);
  float dist_larg_pt = pow(a.larg_pt - b.larg_pt, 2);
  return sqrt(dist_compr_sp + dist_larg_sp + dist_compr_pt + dist_larg_pt);
}

char * classificar_iris(struct Iris incog, struct Iris *iris, int n){
  int best_fit_i = 0;
  float best_fit = dist_euclid_iris(incog, iris[0]);

  for(int i = 1; i < n; i++){
    float dist = dist_euclid_iris(incog, iris[i]);
    if(dist < best_fit){
      best_fit = dist;
      best_fit_i = i;
    }
  }

  return iris[best_fit_i].tipo;
}
