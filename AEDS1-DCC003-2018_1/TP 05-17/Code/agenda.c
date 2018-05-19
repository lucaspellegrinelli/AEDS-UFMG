#include <stdio.h>
#include <stdlib.h>

#define EVENT_COUNT 3

enum Mes {jan = 1, fev = 2, mar = 3, abr = 4, mai = 5, jun = 6, jul = 7, ago = 8, set = 9, out = 10, nov = 11, dez = 12};

struct Data{
  int dia;
  enum Mes mes;
  int ano;
};

struct Evento{
  char nome[100];
  char local[100];
  struct Data data;
};

void cadastrar_eventos(struct Evento *agenda, int n);
void imprimir_eventos(struct Evento agenda[], struct Data d, int n);

int main(){
  struct Evento eventos[EVENT_COUNT];
  cadastrar_eventos(eventos, EVENT_COUNT);

  struct Data data_esp;
  int mes_input;
  scanf("%d", &data_esp.dia);
  scanf("%d", &mes_input);
  data_esp.mes = mes_input;
  scanf("%d", &data_esp.ano);

  imprimir_eventos(eventos, data_esp, EVENT_COUNT);
  return 0;
}

void cadastrar_eventos(struct Evento *agenda, int n){
  for(int i = 0; i < n; i++){
    int mes_input;
    scanf("%s", agenda[i].nome);
    scanf("%s", agenda[i].local);
    scanf("%d", &agenda[i].data.dia);
    scanf("%d", &mes_input);
    agenda[i].data.mes = mes_input;
    scanf("%d", &agenda[i].data.ano);
  }
}

void imprimir_eventos(struct Evento agenda[], struct Data d, int n){
  int eventos_enc = 0;
  for(int i = 0; i < n; i++){
    if(agenda[i].data.dia == d.dia && agenda[i].data.mes == d.mes && agenda[i].data.ano == d.ano){
      eventos_enc++;
      printf("%s %s\n", agenda[i].nome, agenda[i].local);
    }
  }

  if(eventos_enc == 0){
    printf("Nenhum evento encontrado!\n");
  }
}
