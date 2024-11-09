#include "server.h"

int is_next;

void next()
{
    is_next = 1;
}

void excute(handler_list_t *handlers, Request *req, Response *res)
{
    handler_list_t *tmp = handlers;
    is_next = 1;
    while (tmp != NULL && is_next)
    {
        is_next = 0;
        tmp->handler(req, res, next);
        tmp = tmp->next;
    }
}