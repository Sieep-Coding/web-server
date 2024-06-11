#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

void send_response(int client_socket, int status_code, const char *status_message, const char *body, size_t body_len) {
    char status_line[64];
};