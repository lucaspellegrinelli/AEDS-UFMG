#include "common.h"
#include "tag.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>

struct client_data_t {
  int sock;
  struct sockaddr_storage storage;
};

void usage(int argc, char **argv){
  printf("Usage: %s <Server Port>\n", argv[0]);
  exit(EXIT_FAILURE);
}

int process_user_msg(char *msg_buff, char *client_addr_str, int csock){
  int msg_size = strlen(msg_buff);

  int is_message_valid = 1;
  for(int i = 0; i < msg_size; i++){
    if(msg_buff[i] < 0 || msg_buff[i] > 127){
      is_message_valid = 0;
      break;
    }
  }

  if(is_message_valid == 0) return 1;
  if(msg_size == 0) return 2;
  if(msg_size > 500) return 3;

  if(strcmp(msg_buff, "##kill\n") == 0){
    for(int i = 0; i < usertags_size(user_tags); i++){
      pthread_t user_thread = usertags_get_ith_thread(user_tags, i);
      if(user_thread != pthread_self()){
        pthread_kill(user_thread, 0);
      }
    }

    pthread_kill(pthread_self(), 0);
    return 4;
  }

  char out_buff[BUFF_SIZE];
  memset(out_buff, 0, BUFF_SIZE);

  struct intlist * tag_ids = NULL;
  int tag_count = get_all_tags_in_msg(msg_buff, &tag_ids);

  if(tag_count > 0){ // Se é uma mensagem com tags
    struct intlist * subbed_users = NULL;
    get_all_users_sub(&tag_ids, &subbed_users);

    // printf("There's %d subbed users\n", intlist_size(subbed_users));
    for(int i = 0; i < intlist_size(subbed_users); i++){
      int target_user = intlist_ith(subbed_users, i);
      sprintf(out_buff, "[msg] %s\n", msg_buff);
      msg_size = send(target_user, out_buff, strlen(out_buff) + 1, 0);
    }
  }else if(msg_buff[0] == '+'){ // Se é um pedido de acrescentar uma tag
    char tag_str[strlen(msg_buff) + 1];
    memcpy(tag_str, msg_buff + 1, strlen(msg_buff));

    for(int i = 0; i < strlen(tag_str); i++){
      if(tag_str[i] == '\n') tag_str[i] = '\0';
    }

    int sub_status = add_tag_to_user(csock, tag_str);

    if(sub_status == 0){ // Se ele não era inscrito
      sprintf(out_buff, "subscribed %s\n", msg_buff);
      msg_size = send(csock, out_buff, strlen(out_buff) + 1, 0);
    }else{ // Se ele já é inscrito
      sprintf(out_buff, "already subscribed %s\n", msg_buff);
      msg_size = send(csock, out_buff, strlen(out_buff) + 1, 0);
    }
  }else if(msg_buff[0] == '-'){ // Se é um pedido de retirar uma tag
    char tag_str[strlen(msg_buff) + 1];
    memcpy(tag_str, msg_buff + 1, strlen(msg_buff));

    for(int i = 0; i < strlen(tag_str); i++){
      if(tag_str[i] == '\n') tag_str[i] = '\0';
    }

    // printf("A tag encontrada é '%s'\n", tag_str);

    int sub_status = remove_tag_to_user(csock, tag_str);

    if(sub_status == 0){ // Se ele não era inscrito
      sprintf(out_buff, "not subscribed %s\n", msg_buff);
      msg_size = send(csock, out_buff, strlen(out_buff) + 1, 0);
    }else{ // Se ele já é inscrito
      sprintf(out_buff, "unsubscribed %s\n", msg_buff);
      msg_size = send(csock, out_buff, strlen(out_buff) + 1, 0);
    }
  }else{ // Se nao e nenhuma requisição de tag
    // sprintf(out_buff, "Servidor diz: Mensagem recebida");
    // msg_size = send(client_data->sock, out_buff, strlen(out_buff) + 1, 0);
  }

  // printf("[msg] %s, %d bytes: %s\n", client_addr_str, (int)msg_size, msg_buff);
  printf("[msg] %s\n", msg_buff);
  return 0;
}

void * client_thread(void *data){
  // Pega as informações do struct
  struct client_data_t *client_data = (struct client_data_t *)data;

  //
  usertags_add(&user_tags, client_data->sock, pthread_self());

  // Converte o storage do cliente
  struct sockaddr *client_addr = (struct sockaddr *)(&client_data->storage);

  // Cria uma string com o endereço do cliente
  char client_addr_str[BUFF_SIZE];
  addr_to_str(client_addr, client_addr_str, BUFF_SIZE);
  printf("[log] Connection from %s\n", client_addr_str);

  while(1){
    // Recebe a mensagem que o cliente mandou
    char msg_buff[BUFF_SIZE];
    memset(msg_buff, 0, BUFF_SIZE);

    int total_size = 0;

    while(1){
      int msg_size = recv(client_data->sock, msg_buff + total_size, BUFF_SIZE - total_size, 0);
      total_size += msg_size;
      if(msg_buff[strlen(msg_buff) - 1] == '\n' || msg_size == 0) break;
    }

    if(total_size == 0){
      printf("[log] Connection with %s has been closed on the client side\n", client_addr_str);
      break;
    }

    int error = 0;
    int curr_msg_i = 0;
    char curr_msg[BUFF_SIZE];
    for(size_t i = 0; i < strlen(msg_buff); i++){
      if(msg_buff[i] == '\n'){
        curr_msg[curr_msg_i] = '\0';
        curr_msg_i = 0;

        // Fim de uma mensagem
        error = process_user_msg(curr_msg, client_addr_str, client_data->sock);
      }else{
        curr_msg[curr_msg_i++] = msg_buff[i];
      }
    }

    if(error == 1){
      printf("[log] Disconnected %s due to invalid character\n", client_addr_str);
      break;
    }else if(error == 2){
      printf("[log] Closed connection with %s due to null message\n", client_addr_str);
      break;
    }else if(error == 3){
      printf("[log] Closed connection with %s due to message being too big\n", client_addr_str);
      break;
    }else if(error == 4){
      printf("Triggered end of execution\n");
      break;
    }
  }
  
  // Fecha a conexão com o cliente atual
  close(client_data->sock);
  usertags_remove(&user_tags, client_data->sock);

  // Fecha a thread
  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv){
  // Garante que o usuário passou as coisas corretamente para o programa
  if(argc < 2){
    usage(argc, argv);
  }

  // Pega os parametros recebidos
  char* version = "v4";
  char* port = argv[1];

  // Criando a estrutura que toma conta do endereço da rede
  struct sockaddr_storage storage;

  // Se não puder criar, dê erro
  if(server_sockaddr_init(version, port, &storage) != 0){
    usage(argc, argv);
  }

  // Cria o socket com o protocolo do storage
  int sock = socket(storage.ss_family, SOCK_STREAM, 0);

  // Se o socket não pode ser criado, levante um erro
  if(sock == -1){
    log_exit("socket");
  }

  // Faz com o que o linux nao fique com a porta aberta depois de fechar
  // o programa
  int enable = 1;
  if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0){
    log_exit("setsockopt");
  }

  // Converte o storage em sockaddr
  struct sockaddr *serv_addr = (struct sockaddr *)(&storage);

  // Executa o bind
  if(bind(sock, serv_addr, sizeof(storage)) != 0){
    log_exit("bind");
  }

  // Executa o listen
  const int max_pending_connections = 10;
  if(listen(sock, max_pending_connections) != 0){
    log_exit("listen");
  }

  // Cria uma string com o endereço do servidor
  char addr_str[BUFF_SIZE];
  addr_to_str(serv_addr, addr_str, BUFF_SIZE);
  printf("Bound to %s, waiting connections\n", addr_str);

  // Tratamento de conexões
  while(1){
    // Define a estrutura que vai armazenar o sockaddr do cliente
    struct sockaddr_storage client_storage;
    struct sockaddr *client_addr = (struct sockaddr *)(&client_storage);

    // Aceita a próxima conexão e pega o sockaddr do cliente
    socklen_t client_addr_len = sizeof(client_storage);
    int client_sock = accept(sock, client_addr, &client_addr_len);

    // Se a conexão deu problema
    if(client_sock == -1){
      log_exit("accept");
    }

    // Cria o struct onde vamos armazenar os dados do cliente
    struct client_data_t *thread_data = malloc(sizeof(*thread_data));

    // Se nao alocou a memoria, dê erro
    if(!thread_data){
      log_exit("malloc");
    }

    // Coloca os dados do cliente no struct
    thread_data->sock = client_sock;
    memcpy(&(thread_data->storage), &client_storage, sizeof(client_storage));

    // Cria uma nova thread fazendo o handling do cliente atual
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, client_thread, thread_data);
  }

  exit(EXIT_SUCCESS);
}