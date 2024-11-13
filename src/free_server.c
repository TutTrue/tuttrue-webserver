#include "server.h"

void free_server(Server *s)
{
  for (int i = 0; i < s->route_count; i++)
  {
    handler_list_t *current = s->routes[i].handlers;
    while (current != NULL)
    {
      handler_list_t *next = current->next;
      free(current);
      current = next;
    }
  }
  free(s);
}