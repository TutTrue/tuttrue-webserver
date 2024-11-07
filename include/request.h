#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEADER_SIZE 1024
#define MAX_BODY_SIZE 1024
#define MAX_METHOD_SIZE 16
#define MAX_URL_SIZE 512
#define MAX_VERSION_SIZE 16
#define MAX_PARAMS_SIZE 7

typedef struct
{
  char *key;
  char *value;
} Param;

typedef struct
{
  char method[MAX_METHOD_SIZE];
  char url[MAX_URL_SIZE];
  char version[MAX_VERSION_SIZE];
  char headers[MAX_HEADER_SIZE];
  int content_length;
  char body[MAX_BODY_SIZE];
  Param params[MAX_PARAMS_SIZE];
} Request;

int parse_request(const char *request, Request *http_request);
int compare_route(char *url, char *path);
void parse_request_params(Request *req, char *path);
void free_request_params(Request *req);
char *get_param(Request *req, char *key);

#endif
