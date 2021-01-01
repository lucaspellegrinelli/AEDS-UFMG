#pragma once

#include <stdlib.h>
#include <arpa/inet.h>

void log_exit(const char *msg);
int addr_parse(const char *addr_str, const char *port_str,
               struct sockaddr_storage *storage);
void addr_to_str(const struct sockaddr *addr, char *out, size_t outsize);
int server_sockaddr_init(const char *version_str, const char *port_str,
                         struct sockaddr_storage *storage);