#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request.h"
#include "utils.h"

Request *parse_request(char *buffer, size_t buffer_size) {
    Request *request = malloc(sizeof(Request));
    if (request == NULL) {
        return NULL;
    }

    char *method_end = strchr(buffer, ' ');
    if(method_end==NULL) {
        free(request);
        return NULL;
    }
    request -> method = malloc(method_end - buffer + 1);
    if(request -> method == NULL) {
        free(request);
        return NULL;
    }
    strncpy(request -> method, buffer, method_end - buffer);
    request -> method[method_end - buffer] = '\0';

    char *path_start = method_end + 1;
    char *path_end = strchr(path_start, ' ');
    if (path_end==NULL) {
        free(request->method);
        free(request);
        return NULL;
    }
}