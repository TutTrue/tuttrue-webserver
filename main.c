#include "server.h"

#define route(server, method, path, ...) route_d(server, method, path, __VA_ARGS__, NULL)

void say_hello(Request *req, Response *res)
{
  return html(res, HTTP_CREATED, "<html><h1>Hello Route</h1></html>");
}

void say_hi(Request *req, Response *res)
{
  return json(res, HTTP_OK, "{\"Hi?\": \"Hi\"}");
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

  return json(res, HTTP_CREATED, "{\"JSON?\": \"Kinda JSON\"}");
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
    return text(res, HTTP_OK, "X is One function four will not excute");
  }
}
void four(Request *req, Response *res)
{
  printf("four Route\n");
  return text(res, HTTP_OK, "Four Route");
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
