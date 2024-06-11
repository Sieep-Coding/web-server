#ifndef REQUEST_H
#define REQUEST_H

#include <stddef.h>

typedef struct {
    char *method;
    char *path;
    char *protocol;
} Request;

Request *parse_request(char *buffer, size_t buffer_size);
void free_request(Request *request);


#endif