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

void say_hello(Request* req, Response* res)
{
  res->status_code = 200;
  res->content_type = "text/html";
  res->body = "<html><h1>Hello Route</h1></html>";
}

void say_hi(Request* req, Response* res)
{
  res->status_code = 200;
  res->content_type = "text/html";
  res->body = "<html><h1>Hi Route</h1></html>";
}

int main()
{
  Server* tut = create_server();

  route(tut, "GET", "/hello", say_hello);
  route(tut, "POST", "/hi", say_hi);

  tlisten(tut, 4000);

  return 0;
}
