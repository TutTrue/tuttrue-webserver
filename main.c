#include "server.h"

/**
 *
 * req: {
 *   method,
 *   url,
 *   version,
 *   headers,
 *   content_length -> int,
 *   body
 * }
 *
 * res: {
 *  status_code,
 *  headers,
 *  content_type,
 *  body
 * }
 *
 **/

void say_hello(Request *req, Response *res)
{
  res->status_code = 200;
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

  res->status_code = 200;
  res->content_type = "text/json";
  res->body = "{\"JSON?\": \"Kinda JSON\"}";
}

int main()
{
  Server *tut = create_server();

  route(tut, "GET", "/hello", say_hello);
  route(tut, "POST", "/hi", say_hi);
  route(tut, "GET", "/hi/:id/hi/:name/:age/hello", say_hi_with_params);

  tlisten(tut, 4000);

  return 0;
}
