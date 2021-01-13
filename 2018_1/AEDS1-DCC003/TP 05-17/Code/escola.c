#include <stdio.h>
#include <stdlib.h>

#define NUM_ALUNOS 5
#define NUM_MATERIAS 4

struct Aluno{
  char nome[100];
  int num_matric;
  float notas[NUM_MATERIAS];
  float media;
};

void cadastrar_alunos(struct Aluno *alunos, int n);
void imprimir_informacoes(struct Aluno *alunos, int n);

int main(){
  struct Aluno alunos[NUM_ALUNOS];
  cadastrar_alunos(alunos, NUM_ALUNOS);
  imprimir_informacoes(alunos, NUM_ALUNOS);
  return 0;
}

void cadastrar_alunos(struct Aluno *alunos, int n){
  for(int i = 0; i < n; i++){
    scanf("%s", alunos[i].nome);
    scanf("%d", &alunos[i].num_matric);

    alunos[i].media = 0.0;
    for(int j = 0; j < NUM_MATERIAS; j++){
      scanf("%f", &alunos[i].notas[j]);
      alunos[i].media += alunos[i].notas[j];
    }

    alunos[i].media /= NUM_MATERIAS;
  }
}

void imprimir_informacoes(struct Aluno *alunos, int n){
  int melhor_media_i = -1;
  float melhor_media = 0.0;
  int pior_media_i = -1;
  float pior_media = 100.0;
  float media_turma = 0.0;

  for(int i = 0; i < n; i++){
    if(alunos[i].media > melhor_media){
      melhor_media = alunos[i].media;
      melhor_media_i = i;
    }

    if(alunos[i].media < pior_media){
      pior_media = alunos[i].media;
      pior_media_i = i;
    }

    media_turma += alunos[i].media;
  }

  printf("Maior media\nAluno: %s - %d\nMedia: %.2f\n", alunos[melhor_media_i].nome, alunos[melhor_media_i].num_matric, melhor_media);
  printf("Menor media\nAluno: %s - %d\nMedia: %.2f\n", alunos[pior_media_i].nome, alunos[pior_media_i].num_matric, pior_media);
  printf("Media geral: %.2f\n", media_turma / n);
}
