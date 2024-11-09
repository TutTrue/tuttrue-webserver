#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdarg.h>

#include "request.h"
#include "response.h"

#define MAX_ROUTE_COUNT 1024

typedef void (*Next)();
typedef void (*handler_t)(Request *, Response *, Next);

typedef struct handler_list
{
  struct handler_list *next;
  handler_t handler;
} handler_list_t;

typedef struct
{
  char *path;
  char *method;
  handler_list_t *handlers;
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
void route_d(Server *server, char *method, char *path, ...);
void handle_request(Server *server, char *buffer, int new_socket);
void excute(handler_list_t *handlers, Request *req, Response *res);

#endif
