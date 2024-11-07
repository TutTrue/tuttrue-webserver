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
  res->status_code = 200;
  res->content_type = "text/html";
  res->body = "<html><h1>Hi Route</h1></html>";
}

void say_hi1(Request *req, Response *res)
{
  res->status_code = 200;
  res->content_type = "text/plain";
  res->body = "1";
}

void say_hi2(Request *req, Response *res)
{
  res->status_code = 200;
  res->content_type = "text/plain";
  res->body = "2";
}

void say_hi3(Request *req, Response *res)
{
  res->status_code = 200;
  res->content_type = "text/plain";
  res->body = "3";
}

void say_hi4(Request *req, Response *res)
{
  res->status_code = 200;
  res->content_type = "text/plain";
  res->body = "4";
}

void say_hi5(Request *req, Response *res)
{
  res->status_code = 200;
  res->content_type = "text/plain";
  res->body = "5";
}

int main()
{
  Server *tut = create_server();

  route(tut, "GET", "/hello", say_hello);
  route(tut, "POST", "/hi", say_hi);
  route(tut, "GET", "/hi/:id", say_hi1);
  route(tut, "GET", "/hi/:id/hi", say_hi2);
  route(tut, "GET", "/hi/:id/hi/:name", say_hi3);
  route(tut, "GET", "/hi/:id/hi/:name/:age", say_hi4);
  route(tut, "GET", "/hi/:id/hi/:name/:age/hello", say_hi5);

  tlisten(tut, 4000);

  return 0;
}
