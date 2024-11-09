#include "server.h"

handler_list_t *parse_handlers(va_list args)
{
  handler_list_t *handlers = malloc(sizeof(handler_list_t));
  handler_t handler = va_arg(args, handler_t);
  handler_list_t *cur = handlers;
  while (handler != NULL)
  {
    cur->handler = handler;
    handler = va_arg(args, handler_t);

    if (handler != NULL)
    {
      cur->next = malloc(sizeof(handler_list_t));
      cur = cur->next;
    }
    else
    {
      cur->next = NULL;
    }
  }
  return handlers;
}

void route_d(Server *server, char *method, char *path, ...)
{
  if (server->route_count == MAX_ROUTE_COUNT)
  {
    printf("Failed to add route: %s\n", path);
    printf("Max route count reached\n");
    exit(EXIT_FAILURE);
  }

  va_list args;
  va_start(args, path);
  handler_list_t *handlers = parse_handlers(args); // convert va_list to handler_list_t
  va_end(args);

  server->routes[server->route_count].path = path;
  server->routes[server->route_count].method = method;
  server->routes[server->route_count].handlers = handlers;
  server->route_count++;
}
