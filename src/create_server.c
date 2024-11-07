#include "server.h"

Server *create_server()
{
  int server_fd;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  Server *s = malloc(sizeof(Server));
  s->fd = server_fd;
  s->route_count = 0;

  return s;
}
