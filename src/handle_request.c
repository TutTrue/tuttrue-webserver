#include <time.h>
#include "server.h"

void create_response(char *buffer, Response *res)
{
  int i = 0;
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

void default_response(Response *res)
{
  res->status_code = 200;
}

int compare_route(char *url, char *path)
{
  int i = 0, j = 0;
  while (path[i] != '\0' && url[j] != '\0')
  {
    if (path[i] == ':')
    {
      while (url[j] != '/' && url[j] != '\0')
      {
        j++;
      }
      while (path[i] != '/' && path[i] != '\0')
      {
        i++;
      }
    }
    else if (path[i] == url[j])
    {
      i++;
      j++;
    }
    else
    {
      return -1;
    }
  }

  return path[i] == '\0' && url[j] == '\0' ? 0 : -1;
}

void parse_request_params(Request *req, char *path)
{
  int i = 0, j = 0, param_idx = 0;

  while (path[i] != '\0' && req->url[j] != '\0')
  {
    if (path[i] == ':')
    {
      if (param_idx == MAX_PARAMS_SIZE - 1)
        break;
      int key_start = i + 1;

      while (path[i] != '/' && path[i] != '\0')
      {
        i++;
      }

      int key_len = i - key_start;
      req->params[param_idx].key = (char *)malloc(key_len + 1);
      if (!req->params[param_idx].key)
      {
        printf("Failed to allocate params key\n");
        return;
      }
      strncpy(req->params[param_idx].key, &path[key_start], key_len);
      req->params[param_idx].key[key_len] = '\0';

      int value_start = j;
      while (req->url[j] != '/' && req->url[j] != '\0')
      {
        j++;
      }

      int value_len = j - value_start;
      req->params[param_idx].value = (char *)malloc(value_len + 1);
      if (!req->params[param_idx].value)
      {
        printf("Failed to allocate params value\n");
        return;
      }
      strncpy(req->params[param_idx].value, &req->url[value_start], value_len);
      req->params[param_idx].value[value_len] = '\0';

      param_idx++;
    }
    else
    {
      i++;
      j++;
    }
  }
  req->params[param_idx].key = NULL;
  req->params[param_idx].value = NULL;
}

void free_request_params(Request *req)
{
  int v = 0;
  while (req->params[v].key != NULL)
  {
    free(req->params[v].key);
    free(req->params[v].value);
    v += 1;
  }
}

void handle_request(Server *server, char *buffer, int new_socket)
{
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

  for (int i = 0; i < server->route_count; i++)
  {
    if (strcmp(req.method, server->routes[i].method) == 0 && compare_route(req.url, server->routes[i].path) == 0)
    {
      parse_request_params(&req, server->routes[i].path);
      server->routes[i].handler(&req, &res);
      free_request_params(&req);
      create_response(b, &res);
      found_route = 1;
      break;
    }
  }
  if (found_route)
  {
    send(new_socket, b, strlen(b), 0);
  }
  else
  {
    res.status_code = 404;
    printf("Route not found ");
  }
  clock_t end_time = clock();
  double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
  printf("%s %s %d -> %f millisecond\n", req.method, req.url, res.status_code, time_taken);
}
