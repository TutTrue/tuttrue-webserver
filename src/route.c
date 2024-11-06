#include "server.h"

void route(Server* server, char* method, char* path, void (*handler)(Request*, Response*))
{
  if (server->route_count == MAX_ROUTE_COUNT) {
    printf("Failed to add route: %s\n", path);
    printf("Max route count reached\n");
    exit(EXIT_FAILURE);
  }
  server->routes[server->route_count].path = path;
  server->routes[server->route_count].handler = handler;
  server->routes[server->route_count].method = method;
  server->route_count++;
}
