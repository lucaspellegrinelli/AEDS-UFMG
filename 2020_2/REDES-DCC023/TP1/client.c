#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

struct client_data_t {
  int sock;
};

void usage(int argc, char **argv){
  printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
  exit(EXIT_FAILURE);
}

void * listen_thread(void *data){
  // Pega as informações do struct
  struct client_data_t *client_data = (struct client_data_t *)data;

  while(1){
    // Cria um buffer para armazenar as mensagens
    char data_buff[BUFF_SIZE];
    memset(data_buff, 0, BUFF_SIZE);

    // Recebe a mensagem do servidor e coloca no buffer
    size_t total_size = 0;

    while(1){
      size_t msg_size = recv(client_data->sock, data_buff, BUFF_SIZE, 0);
      total_size += msg_size;
      if(data_buff[strlen(data_buff) - 1] == '\n' || msg_size == 0) break;
    }

    // Caso nada tenha sido recebido, a conexão acabou
    if(total_size == 0){
      close(client_data->sock);
      pthread_exit(EXIT_SUCCESS);
    }

    int curr_msg_i = 0;
    char curr_msg[BUFF_SIZE];
    for(size_t i = 0; i < total_size; i++){
      if(data_buff[i] == '\n'){
        curr_msg[curr_msg_i] = '\0';
        curr_msg_i = 0;

        if(strcmp("##kill", curr_msg) == 0){
          close(client_data->sock);
          exit(EXIT_SUCCESS);
        }else{
          printf("%s\n", curr_msg);
        }
      }else{
        curr_msg[curr_msg_i++] = data_buff[i];
      }
    }
  }
}

int main(int argc, char **argv){
  // Garante que o usuário passou as coisas corretamente para o programa
  if(argc < 3){
    usage(argc, argv);
  }

  // Pega os parametros recebidos
  char* ip = argv[1];
  char* port = argv[2];

  // Criando a estrutura que toma conta do endereço da rede
  struct sockaddr_storage storage;

  // Se não puder criar, dê erro
  if(addr_parse(ip, port, &storage) != 0){
    usage(argc, argv);
  }

  // Cria o socket com o protocolo do storage
  int sock = socket(storage.ss_family, SOCK_STREAM, 0);

  // Se o socket não pode ser criado, levante um erro
  if(sock == -1){
    log_exit("socket");
  }

  // Converte o storage em sockaddr
  struct sockaddr *serv_addr = (struct sockaddr *)(&storage);

  // Tente conectar no servidor, caso falhe, levante um erro
  if(connect(sock, serv_addr, sizeof(storage)) != 0){
    log_exit("connect");
  }

  // Cria uma string com o endereço do servidor
  char addr_str[BUFF_SIZE];
  addr_to_str(serv_addr, addr_str, BUFF_SIZE);
  printf("Connected to %s\n", addr_str);

  // Cria o struct onde vamos armazenar os dados do cliente
  struct client_data_t *thread_data = malloc(sizeof(*thread_data));
  thread_data->sock = sock;

  // Cria uma nova thread fazendo o handling do cliente atual
  pthread_t listen_thread_id;
  pthread_create(&listen_thread_id, NULL, listen_thread, thread_data);

  while(1){
    // Cria um buffer para armazenar as mensagens
    char data_buff[BUFF_SIZE];
    memset(data_buff, 0, BUFF_SIZE);

    // Pede para o usuário qual a mensagem à ser mandada
    // printf(" > ");
    fgets(data_buff, BUFF_SIZE - 1, stdin);

    // Manda a mensagem para o servidor
    size_t msg_size = send(sock, data_buff, strlen(data_buff) + 1, 0);

    // Caso o número de dados enviados não seja igual ao número
    // de caracteres na mensagem, deu ruim
    if(msg_size != strlen(data_buff) + 1){
      close(sock);
      log_exit("send");
    }
  }

  // pthread_t send_thread_id;
  // pthread_create(&send_thread_id, NULL, send_thread, thread_data);

  exit(EXIT_SUCCESS);
}