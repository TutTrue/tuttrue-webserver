#include "response.h"

void json(Response *res, HttpStatusCode code, char *body)
{
  res->status_code = code;
  res->content_type = "text/json";
  res->body = body;
}

void html(Response *res, HttpStatusCode code, char *body)
{
  res->status_code = code;
  res->content_type = "text/html";
  res->body = body;
}

void text(Response *res, HttpStatusCode code, char *body)
{
  res->status_code = code;
  res->content_type = "text/plain";
  res->body = body;
}