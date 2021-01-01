#include "common.h"
#include "tag.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

struct client_data_t {
  int sock;
  struct sockaddr_storage storage;
};

void usage(int argc, char **argv){
  printf("Usage: %s <Server Port>\n", argv[0]);
  exit(EXIT_FAILURE);
}

void * client_thread(void *data){
  int user_tags[MAX_USER_TAGS];
  for(int i = 0; i < MAX_USER_TAGS; i++) user_tags[i] = -1;

  // Pega as informações do struct
  struct client_data_t *client_data = (struct client_data_t *)data;

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
    size_t msg_size = recv(client_data->sock, msg_buff, BUFF_SIZE, 0);

    char out_buff[BUFF_SIZE];
    memset(out_buff, 0, BUFF_SIZE);

    if(msg_size == 0){
      printf("[log] Closed connection with %s\n", client_addr_str);
      break;
    }

    if(msg_buff[0] == '+'){ // Se é um pedido de acrescentar uma tag
      char tag_str[strlen(msg_buff) + 1];
      memcpy(tag_str, msg_buff + 1, strlen(msg_buff));
      int sub_status = add_tag_to_user(user_tags, tag_str);

      if(sub_status == 0){ // Se ele não era inscrito
        sprintf(out_buff, "subscribed %s", msg_buff);
        msg_size = send(client_data->sock, out_buff, strlen(out_buff) + 1, 0);
      }else{ // Se ele já é inscrito
        sprintf(out_buff, "already subscribed %s", msg_buff);
        msg_size = send(client_data->sock, out_buff, strlen(out_buff) + 1, 0);
      }
    }else if(msg_buff[0] == '-'){ // Se é um pedido de retirar uma tag
      char tag_str[strlen(msg_buff) + 1];
      memcpy(tag_str, msg_buff + 1, strlen(msg_buff));
      int sub_status = remove_tag_to_user(user_tags, tag_str);

      if(sub_status == 0){ // Se ele não era inscrito
        sprintf(out_buff, "not subscribed %s", msg_buff);
        msg_size = send(client_data->sock, out_buff, strlen(out_buff) + 1, 0);
      }else{ // Se ele já é inscrito
        sprintf(out_buff, "unsubscribed %s", msg_buff);
        msg_size = send(client_data->sock, out_buff, strlen(out_buff) + 1, 0);
      }
    }else{ // Se nao e nenhuma requisição de tag
      sprintf(out_buff, "Servidor diz: Mensagem recebida");
      msg_size = send(client_data->sock, out_buff, strlen(out_buff) + 1, 0);
    }

    printf("[msg] %s, %d bytes: %s", client_addr_str, (int)msg_size, msg_buff);

    // Caso o número de dados enviados não seja igual ao número
    // de caracteres na mensagem, deu ruim
    if(msg_size != strlen(out_buff) + 1){
      log_exit("send");
    }
  }
  
  // Fecha a conexão com o cliente atual
  close(client_data->sock);

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