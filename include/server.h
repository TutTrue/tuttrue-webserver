#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "request.h"
#include "response.h"

#define MAX_ROUTE_COUNT 1024

typedef struct
{
  char *path;
  char *method;
  void (*handler)(Request *, Response *);
} Route;

typedef struct
{
  int fd;
  int port;
  Route routes[MAX_ROUTE_COUNT];
  int route_count;
} Server;

Server *create_server();
void tlisten(Server *s, int port);
void route(Server *server, char *method, char *path, void (*handler)(Request *, Response *));
void handle_request(Server *server, char *buffer, int new_socket);

#endif
