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

typedef struct {
    char method[MAX_METHOD_SIZE];
    char url[MAX_URL_SIZE];
    char version[MAX_VERSION_SIZE];
    char headers[MAX_HEADER_SIZE];
    int content_length;
    char body[MAX_BODY_SIZE];
} Request;


int parse_request(const char *request, Request *http_request);

#endif
