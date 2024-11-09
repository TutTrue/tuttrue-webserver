#include "server.h"

#define route(server, method, path, ...) route_d(server, method, path, __VA_ARGS__, NULL)

void say_hello(Request *req, Response *res)
{
  res->status_code = 201;
  res->content_type = "text/html";
  res->body = "<html><h1>Hello Route</h1></html>";
}

void say_hi(Request *req, Response *res)
{
  res->status_code = 201;
  res->content_type = "text/html";
  res->body = "<html><h1>Hi Route</h1></html>";
}

void say_hi_with_params(Request *req, Response *res)
{
  char *id = get_param(req, "id");
  char *name = get_param(req, "name");
  char *age = get_param(req, "age");
  char *not_found = get_param(req, "NOTFOUND");

  printf("id: %s\n", id);
  printf("name: %s\n", name);
  printf("age: %s\n", age);
  printf("not_found: %s\n", not_found);

  res->status_code = 201;
  res->content_type = "text/json";
  res->body = "{\"JSON?\": \"Kinda JSON\"}";
}
void one(Request *req, Response *res, Next next)
{
  next();
}
void two(Request *req, Response *res, Next next)
{
  next();
}
void three(Request *req, Response *res, Next next)
{
  int x = 1;
  if (x == 0)
  {
    next();
  }
  else
  {
    res->status_code = 201;
    res->content_type = "text/html";
    res->body = "<html><h1>X is One function four will not excute</h1></html>";
  }
}
void four(Request *req, Response *res)
{
  printf("four Route\n");
  res->status_code = 201;
  res->content_type = "text/html";
  res->body = "<html><h1>Four Route</h1></html>";
}

int main()
{
  Server *tut = create_server();

  route(tut, "GET", "/count", one, two, three, four);
  route(tut, "GET", "/hello", say_hello);
  route(tut, "POST", "/hi", say_hi);
  route(tut, "GET", "/hi", say_hi);
  route(tut, "GET", "/hi/:id/hi/:name/:age/hello", say_hi_with_params);

  tlisten(tut, 4000);

  return 0;
}
