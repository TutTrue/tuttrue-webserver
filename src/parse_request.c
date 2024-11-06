#include <string.h>
#include <stdlib.h>
#include "request.h"

int parse_request(const char *request, Request *http_request) {
    char *request_copy = strdup(request);
    if (request_copy == NULL) return -1;

    char *line, *saveptr;

    line = strtok_r(request_copy, "\r\n", &saveptr);
    if (line == NULL) {
        free(request_copy);
        return -1;
    }

    sscanf(line, "%s %s %s", http_request->method, http_request->url, http_request->version);

    http_request->headers[0] = '\0';
    http_request->content_length = 0;

  // TODO: headers contains the body of the request as well. Fix this.
    while ((line = strtok_r(NULL, "\r\n", &saveptr)) != NULL) {
        if (strlen(line) == 0) break;

        if (strncmp(line, "Content-Length:", 15) == 0) {
            sscanf(line, "Content-Length: %d", &http_request->content_length);
        }

        strcat(http_request->headers, line);
        strcat(http_request->headers, "\r\n");
    }

    char *body_start = strstr(request, "\r\n\r\n");
    if (body_start != NULL) {
        body_start += 4;

        if (http_request->content_length > 0) {
            strncpy(http_request->body, body_start, http_request->content_length);
            http_request->body[http_request->content_length] = '\0'; // Ensure null termination
        }
    } else {
        http_request->body[0] = '\0';
    }

    free(request_copy);
    return 0;
}

