#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define BUFF_SIZE 1024

void usage(int argc, char **argv){
  printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
  exit(EXIT_FAILURE);
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

  while(1){
    // Cria um buffer para armazenar as mensagens
    char data_buff[BUFF_SIZE];
    memset(data_buff, 0, BUFF_SIZE);
    
    // Pede para o usuário qual a mensagem à ser mandada
    printf("mensagem > ");
    fgets(data_buff, BUFF_SIZE - 1, stdin);

    // Manda a mensagem para o servidor
    size_t msg_size = send(sock, data_buff, strlen(data_buff) + 1, 0);

    // Caso o número de dados enviados não seja igual ao número
    // de caracteres na mensagem, deu ruim
    if(msg_size != strlen(data_buff) + 1){
      log_exit("send");
    }

    // Reseta o conteudo do buffer de mensagem para agora receber
    // os valores do servidor
    memset(data_buff, 0, BUFF_SIZE);

    // Recebe a mensagem do servidor e coloca no buffer
    msg_size = recv(sock, data_buff, BUFF_SIZE, 0);

    // Caso nada tenha sido recebido, a conexão acabou
    if(msg_size == 0){
      break;
    }

    // Mostra estatísticas da conexão
    // printf("Recieved %lu bytes\n", msg_size);
    puts(data_buff);
  }

  // Fecha o socket
  close(sock);

  exit(EXIT_SUCCESS);
}