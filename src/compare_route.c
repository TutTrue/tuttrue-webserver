#include "request.h"

int compare_route(char *url, char *path)
{
    int i = 0, j = 0;
    while (path[i] != '\0' && url[j] != '\0')
    {
        if (path[i] == ':')
        {
            while (url[j] != '/' && url[j] != '\0')
                j++;
            while (path[i] != '/' && path[i] != '\0')
                i++;
        }
        else if (path[i] == url[j])
        {
            i++;
            j++;
        }
        else
        {
            return -1;
        }
    }

    return path[i] == '\0' && url[j] == '\0' ? 0 : -1;
}
