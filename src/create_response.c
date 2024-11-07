#include <string.h>
#include "response.h"

void create_response(char *buffer, Response *res)
{
    int i = 0;
    i += sprintf(buffer, "HTTP/1.1 %d %s\r\n", res->status_code, get_status_text(res->status_code));
    if (res->headers != NULL)
        i += sprintf(buffer + i, "%s", res->headers);
    if (res->content_type != NULL)
        i += sprintf(buffer + i, "Content-Type: %s\r\n", res->content_type);
    if (res->body != NULL)
    {
        i += sprintf(buffer + i, "Content-Length: %ld\r\n", strlen(res->body));
        i += sprintf(buffer + i, "\r\n");
        i += sprintf(buffer + i, "%s", res->body);
        sprintf(buffer + i, "\r\n");
    }
}
