#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Classe para guardar as informações de id do personagem e quantidade de vezes
// que ele usará o microondas
class Personagem {
  public:
  int personagem_id;
  int quantidade;

  Personagem(int personagem_id, int quantidade){
    this->personagem_id = personagem_id;
    this->quantidade = quantidade;
  }
};

// Condição para controlar quando as threads podem checar se é a vez delas na fila
pthread_cond_t esquentar_cond = PTHREAD_COND_INITIALIZER;

// Mutex para controlar o acesso ao forno
pthread_mutex_t forno_mut = PTHREAD_MUTEX_INITIALIZER;

// Mutex para controlar o acesso a fila
pthread_mutex_t fila_mut = PTHREAD_MUTEX_INITIALIZER;

// Número de threads a serem criadas para os personagens (exceto Raj)
const int thread_count = 8;

// Número de threads atualmente abertas (serve como condição de parada
// para Raj)
int threads_abertas = 0;

// Caso esse valor seja diferente de -1, significa que aquele valor é o id
// do personagem que o Raj escolheu para passar
int raj_escolha = -1;

// Vetor de nomes indexados
std::string nomes[thread_count] = {
  "Sheldon",
  "Amy",
  "Leonard",
  "Penny",
  "Howard",
  "Bernadette",
  "Stuart",
  "Kripke"
};

// Vetor indicando qual o índice dos perceiros(as) de cada personagem
int perceirxs[thread_count] = {
  1,  // Sheldon (0) => Amy (1)
  0,  // Amy (1) => Sheldon (0)
  3,  // Leonard (2) => Penny (3)
  2,  // Penny (3) => Leonard (2)
  5,  // Howard (4) => Bernadette (5)
  4,  // Bernadette (5) => Howard (4)
  -1, // Stuart (6) => Ninguem (-1)
  -1, // Kripke (7) => Ninguem (-1)
};

// Vetor contendo em cada posição o índice do personagem que ocupa aquela
// posição assim como se ele está ou não com seu/sua parceiro(a)
std::vector<std::pair<int, bool>> fila;

// Remove um personagem da fila arrumando (caso exista)
void remover_da_fila(int personagem){
  for(size_t i = 0; i < fila.size(); i++) {
    if(fila[i].first == personagem){
      fila.erase(fila.begin() + i);
      break;
    }
  }
}

// Checa de um determinado personagem está ou não na fila
bool esta_na_lista(int personagem){
  for(size_t i = 0; i < fila.size(); i++) {
    if(fila[i].first == personagem){
      return true;
    }
  }

  return false;
}

// Checa se existe deadlock. Um deadlock ocorrerá no problema se somente se
// existe pelo menos um membro de cada casal simultaneamente esperando na fila.
// Nesse caso temos um loop de precedências.
bool tem_deadlock(){
  bool sheldon = esta_na_lista(0) || esta_na_lista(1); // Caso um membro do casal do Sheldon esteja na fila
  bool leonard = esta_na_lista(2) || esta_na_lista(3); // Caso um membro do casal do Leonard esteja na fila
  bool howard = esta_na_lista(4) || esta_na_lista(5); // Caso um membro do casal do Howard esteja na fila
  return sheldon && leonard && howard;
}

// Retorna quem tem preferência entre dois personagens. Caso o valor de retorno seja 1,
// o personagem "per_a" tem preferência sobre o personagem "per_b" e vice versa.
int quem_vai_na_frente(std::pair<int, bool> per_a, std::pair<int, bool> per_b){
  // Transforma o índica das parceiras no mesmo índice dos parceiros
  if(per_a.first % 2 == 1 && per_a.first <= 5){
    per_a.first -= 1;
  }

  if(per_b.first % 2 == 1 && per_b.first <= 5){
    per_b.first -= 1;
  }

  // Se forem um casal, mantenha a ordem de entrada
  if(per_a == per_b) return 1;

  // Se algum dos dois tem casal, ele vai na frente
  if(per_a.second && !per_b.second) return 1;
  if(!per_a.second && per_b.second) return -1;

  // Sheldon e Howard
  if(per_a.first == 0 && per_b.first == 4) return 1;
  if(per_a.first == 4 && per_b.first == 0) return -1;

  // Howard e Leonard
  if(per_a.first == 4 && per_b.first == 2) return 1;
  if(per_a.first == 2 && per_b.first == 4) return -1;

  // Leonard e Sheldon
  if(per_a.first == 2 && per_b.first == 0) return 1;
  if(per_a.first == 0 && per_b.first == 2) return -1;

  // Stuart
  if(per_a.first == 6 && per_b.first == 7) return 1;
  if(per_a.first == 7 && per_b.first == 6) return -1;
  if(per_a.first == 6) return -1;
  if(per_b.first == 6) return 1;

  // Kripke
  if(per_a.first == 7) return -1;
  if(per_b.first == 7) return 1;

  // Se nao for nenhum desses, mantenha a ordem de entrada
  return 1;
}

// Retorna o índice do próximo personagem da fila
int proximo_da_fila(){
  if(tem_deadlock()){ // Caso tenha deadlock, dê um erro "-1"
    return -1;
  }else if(fila.size() == 0){ // Caso a lista seja vazia, dê um erro "-2"
    return -2;  
  }else{ // Caso esteja tudo certo, calcule quem tem maior preferência
    std::pair<int, bool> prox = fila[0];
    for(size_t i = 1; i < fila.size(); i++) {
      if(quem_vai_na_frente(prox, fila[i]) == -1){
        prox = fila[i];
      }
    }

    return prox.first;
  }
}

// Coloca um novo personagem na fila, levando em consideração se seu parceirxs
// já está ou não na fila, atualizando a booleana correspondente.
void inserir_na_fila(int personagem){
  pthread_mutex_lock(&fila_mut); // Trava o mutex da fila

  // Encontra o parceirx do personagem caso exista
  int perceirx_id = -1;
  for(size_t i = 0; i < fila.size(); i++){
    if(fila[i].first == perceirxs[personagem]){
      perceirx_id = i;
    }
  }

  if(perceirx_id >= 0){ // Se o parceirx está na lista
    fila[perceirx_id].second = true;
    fila.push_back({ personagem, true });
  }else{
    fila.push_back({ personagem, false });
  }

  printf("%s quer usar o forno\n", nomes[personagem].c_str());
  pthread_mutex_unlock(&fila_mut); // Destrava o mutex da fila
}

// Método relacionado a ação de esperar para esquentar a comida
void esquentar_comida(int personagem){
  pthread_mutex_lock(&forno_mut); // Travar o mutex do forno

  // Caso não seja a vez do personagem atual, 
  while(personagem != proximo_da_fila()){

    // Caso Raj tenha escolhido o personagem atual para liberar, continuemos
    if(personagem == raj_escolha){
      raj_escolha = -1;
      break;
    }

    // Espere até o próximo 'broadcast' para checar se sua vez chegou
    pthread_cond_wait(&esquentar_cond, &forno_mut);
  }

  printf("%s começou a esquentar algo\n", nomes[personagem].c_str());
  remover_da_fila(personagem);
  sleep(1);
  pthread_mutex_unlock(&forno_mut); // Destravar o mutex do forno
}

// Método relacionado a ação de comer (esperar 3-6 segundos)
void comer(int personagem){
  printf("%s vai comer\n", nomes[personagem].c_str());
  int tempo = (rand() % 4) + 3;
  sleep(tempo);
}

// Método relacionado a ação de trabalhar (esperar 3-6 segundos)
void trabalhar(int personagem){
  printf("%s voltou para o trabalho\n", nomes[personagem].c_str());
  int tempo = (rand() % 4) + 3;
  sleep(tempo);
}

// Definição das ações de Raj
void *thread_raj(void *p){

  // Enquanto ainda tenham threads abertas, ou seja, ainda existam personagens
  // executando ações
  while(threads_abertas > 0){

    // Espere 5 segundos
    sleep(5);
    
    // Se existe deadlock, escolha alguem aleatoramente da fila para ser liberado
    // e lance um 'broadcast' para que todos os personagens testem se eles são
    // o próximo da fila ou não.
    if(tem_deadlock()){
      int ind = rand() % fila.size();
      raj_escolha = fila[ind].first;

      printf("Raj detectou um deadlock, liberando %s\n", nomes[raj_escolha].c_str());
      pthread_cond_broadcast(&esquentar_cond); 
    }
  }

  pthread_exit(EXIT_SUCCESS);
}

// Definições das ações dos personagens
void *thread_personagem(void *quem){
  Personagem *quem_t = (Personagem *)quem;

  // Serão feitas 'quem_t->quantidade' ciclos de ações
  for(int i = 0; i < quem_t->quantidade; i++){
    // Entrar na fila
    inserir_na_fila(quem_t->personagem_id);

    // Esquentar a comida
    esquentar_comida(quem_t->personagem_id);
    
    // Assim que acabar de esquentar a comida, é enviado um 'broadcast' para
    // os outros personagens checarem se é a vez deles de esquentar a comida deles
    pthread_cond_broadcast(&esquentar_cond);
    
    // Fazer a ação de comer
    comer(quem_t->personagem_id);

    // Fazer a ação de trabalhar
    trabalhar(quem_t->personagem_id);
  }

  // Ao final da execução das ações desse personagem, diminua o número de threads abertas
  // e delete o objeto criado com suas informações da memória
  threads_abertas--;
  delete (Personagem *) quem;
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  if(argc < 2){
    return 0;
  }

  // Número de ações de cada usuario pega da linha de comando
  int n_acoes = std::atoi(argv[1]);

  // Inicialização do método de aleatoriedade
  srand (time(NULL));

  // Definição das threads
  pthread_t threads[thread_count];
  pthread_t raj_thread;

  // Criação das threads
  for (int i = 0; i < thread_count; i++) {
    threads_abertas++;
    pthread_create(&threads[i], NULL, thread_personagem, new Personagem(i, n_acoes));
  }
  pthread_create(&raj_thread, NULL, thread_raj, NULL);

  // Espera cada uma das threads terminarem
  for(int i = 0; i < thread_count; i++) {
    pthread_join(threads[i], NULL);
  }
  pthread_join(raj_thread, NULL);

  // Limpa a memória dos mutexes e condições
  pthread_mutex_destroy(&fila_mut);
  pthread_mutex_destroy(&forno_mut);
  pthread_cond_destroy(&esquentar_cond);

  return 0;
}