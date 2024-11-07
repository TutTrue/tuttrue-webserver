#include <string.h>
#include <stdlib.h>
#include "request.h"

int parse_request(const char *request, Request *http_request)
{
    char *request_copy = strdup(request);
    if (request_copy == NULL)
        return -1;

    char *line, *saveptr;

    line = strtok_r(request_copy, "\r\n", &saveptr);
    if (line == NULL)
    {
        free(request_copy);
        return -1;
    }

    sscanf(line, "%s %s %s", http_request->method, http_request->url, http_request->version);

    http_request->headers[0] = '\0';
    http_request->content_length = 0;

    // TODO: headers contains the body of the request as well. Fix this.
    while ((line = strtok_r(NULL, "\r\n", &saveptr)) != NULL)
    {
        if (strlen(line) == 0)
            break;

        if (strncmp(line, "Content-Length:", 15) == 0)
        {
            sscanf(line, "Content-Length: %d", &http_request->content_length);
        }

        strcat(http_request->headers, line);
        strcat(http_request->headers, "\r\n");
    }

    char *body_start = strstr(request, "\r\n\r\n");
    if (body_start != NULL)
    {
        body_start += 4;

        if (http_request->content_length > 0)
        {
            strncpy(http_request->body, body_start, http_request->content_length);
            http_request->body[http_request->content_length] = '\0'; // Ensure null termination
        }
    }
    else
    {
        http_request->body[0] = '\0';
    }

    free(request_copy);
    return 0;
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
                i++;

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
                j++;

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
