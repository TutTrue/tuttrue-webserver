#include <time.h>
#include "server.h"

void create_response(char* buffer, Response* res)
{
  int i =0;
  i += sprintf(buffer, "HTTP/1.1 %d %s\r\n", res->status_code, get_status_text(res->status_code));
  if (res->headers != NULL)
    i += sprintf(buffer + i, "%s", res->headers);
  if (res->content_type != NULL)
    i += sprintf(buffer + i, "Content-Type: %s\r\n", res->content_type);
  if (res->body != NULL)
  {
    i += sprintf(buffer + i, "Content-Length: %ld\r\n", strlen(res->body));
    i += sprintf(buffer + i, "\r\n");
    i += sprintf(buffer + i, "%s", res->body);
    sprintf(buffer + i, "\r\n");
  }
}

void default_response(Response* res)
{
  res->status_code = 200;
}


void handle_request(Server* server, char* buffer, int new_socket) {
  Request req;
  Response res;
  char b[1024];
  int found_route = 0;

  clock_t start_time = clock();

  if (parse_request(buffer, &req) != 0)
  {
    printf("Failed to parse request\n");
    exit(EXIT_FAILURE);
  }

  default_response(&res);

  for (int i = 0; i < server->route_count; i++) {
    if (strcmp(req.url, server->routes[i].path) == 0 && strcmp(req.method, server->routes[i].method) == 0)
    {
      server->routes[i].handler(&req, &res);
      create_response(b, &res);
      found_route = 1;
      break;
    }
  }
  if (found_route) {
    send(new_socket, b, strlen(b), 0);
  } else {
    res.status_code = 404;
    printf("Route not found: %s\n", req.url);
  }
  clock_t end_time = clock();
  double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC * 1000;
  printf("%s %s %d -> %f millisecond\n", req.method, req.url, res.status_code, time_taken);
}
