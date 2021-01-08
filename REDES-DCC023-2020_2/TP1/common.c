#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <string.h>

void log_exit(const char *msg){
  perror(msg);
  exit(EXIT_FAILURE);
}

int addr_parse(const char *addr_str, const char *port_str, struct sockaddr_storage *storage){
  // Se o endereço ou a porta forem nulos, retorna com erro
  if(addr_str == NULL || port_str == NULL){
    return -1;
  }

  // Converte a string da port para um inteiro de 16 bits
  uint16_t port = (uint16_t) atoi(port_str);

  // Se a string for inválida, retorne com erro
  if(port == 0){
    return -1;
  }

  // "Host to Network Short (16bits)" serve para converter a ordem
  // dos bits para o formato "Big Endian"
  port = htons(port);

  // Cria uma variável para armazenar o endereço IPv4
  struct in_addr inaddr4;

  // Tenta dar parse na string de endereço para o struct correto
  if(inet_pton(AF_INET, addr_str, &inaddr4)){ // "Presentation to network"
    // Converte o storage para uma variavel de IPv4 e retorna sucesso
    struct sockaddr_in *addrv4 = (struct sockaddr_in *) storage;
    addrv4->sin_family = AF_INET;
    addrv4->sin_port = port;
    addrv4->sin_addr = inaddr4;
    return 0;
  }

  // Caso chegue aqui é porque o endereço não é IPv4, vamos tentar IPv6

  // Cria uma variável para armazenar o endereço IPv6
  struct in6_addr inaddr6;

  // Tenta dar parse na string de endereço para o struct correto
  if(inet_pton(AF_INET6, addr_str, &inaddr6)){ // "Presentation to network"
    // Converte o storage para uma variavel de IPv6 e retorna sucesso
    struct sockaddr_in6 *addrv6 = (struct sockaddr_in6 *) storage;
    addrv6->sin6_family = AF_INET6;
    addrv6->sin6_port = port;

    // addrv6->sin6_addr = inaddr6;
    // Nao pode atribuir porque agora o endereco é um vetor de bytes
    memcpy(&(addrv6->sin6_addr), &inaddr6, sizeof(inaddr6));

    return 0;
  }

  // Se chegar aqui é porque deu errado com IPv4 e IPv6... É a vida
  return -1;
}

void addr_to_str(const struct sockaddr *addr, char *out, size_t outsize){
  int version;
  uint16_t port;
  char addr_str[INET6_ADDRSTRLEN + 1] = "";

  if(addr->sa_family == AF_INET){ // Se for IPv4
    // Converte o addr para uma variavel de IPv4 e retorna sucesso
    struct sockaddr_in *addrv4 = (struct sockaddr_in *) addr;

    // Coloca a version correta
    version = 4;

    // Converte o endereço para a string, se der erro...
    if(!inet_ntop(AF_INET, &(addrv4->sin_addr), addr_str, INET6_ADDRSTRLEN + 1)){ // "Network to presentation"
      log_exit("ntop");
    }

    // Volta o valor da porta para little endian
    port = ntohs(addrv4->sin_port);
  }else if(addr->sa_family == AF_INET6){ // Se for IPv6
    // Converte o addr para uma variavel de IPv4 e retorna sucesso
    struct sockaddr_in6 *addrv6 = (struct sockaddr_in6 *) addr;

    // Coloca a version correta
    version = 6;

    // Converte o endereço para a string, se der erro...
    if(!inet_ntop(AF_INET6, &(addrv6->sin6_addr), addr_str, INET6_ADDRSTRLEN + 1)){ // "Network to presentation"
      log_exit("ntop");
    }

    // Volta o valor da porta para little endian
    port = ntohs(addrv6->sin6_port);
  }else{ // Não sei o protocolo
    log_exit("unknown protocol family");
  }

  // Coloca na variável "out" a string de saida
  if(out){
    snprintf(out, outsize, "IPv%d %s %hu", version, addr_str, port);
  }
}

int server_sockaddr_init(const char *version_str, const char *port_str, struct sockaddr_storage *storage){
  // Converte a string da port para um inteiro de 16 bits
  uint16_t port = (uint16_t) atoi(port_str);

  // Se a string for inválida, retorne com erro
  if(port == 0){
    return -1;
  }

  // "Host to Network Short (16bits)" serve para converter a ordem
  // dos bits para o formato "Big Endian"
  port = htons(port);

  // Inicializando o storage
  memset(storage, 0, sizeof(*storage));

  // Checando qual protocolo a gente deve usar
  if(strcmp(version_str, "v4") == 0){
    // Converte o storage para uma variavel de IPv4 e retorna sucesso
    struct sockaddr_in *addrv4 = (struct sockaddr_in *) storage;
    addrv4->sin_family = AF_INET;
    addrv4->sin_port = port;
    addrv4->sin_addr.s_addr = INADDR_ANY; // Qualquer endereço disponível
    return 0;
  }else if(strcmp(version_str, "v6") == 0){
    // Converte o storage para uma variavel de IPv6 e retorna sucesso
    struct sockaddr_in6 *addrv6 = (struct sockaddr_in6 *) storage;
    addrv6->sin6_family = AF_INET6;
    addrv6->sin6_port = port;
    addrv6->sin6_addr = in6addr_any; // Qualquer endereço disponível
    return 0;
  }else{
    return -1;
  }

  return 0;
}