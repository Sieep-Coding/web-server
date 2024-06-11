#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void send_response(int client_socket, int status_code, const char *status_message, const char *body, size_t body_len);

#endif