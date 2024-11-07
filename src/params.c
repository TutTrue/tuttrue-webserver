#include "request.h"

char *get_param(Request *req, char *key)
{
    int i = 0;
    while (req->params[i].key != NULL)
    {
        if (strcmp(req->params[i].key, key) == 0)
        {
            return req->params[i].value;
        }
        i++;
    }
    return NULL;
}