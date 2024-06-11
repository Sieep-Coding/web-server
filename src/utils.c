#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

void send_response(int client_socket, int status_code, const char *status_message, const char *body, size_t body_len) {
    char status_line[64];
    snprintf(status_line, sizeof(status_line), "HTTP/1.1 %d %s\r\n", status_code, status_message);

    char content_length[64];
    snprintf(content_length, sizeof(content_length), "Content Length: %zu\r\n", body_len);

    char response[4056];

    size_t response_len = snprintf(response, sizeof(response),
                                    "%s%s\r\n%s",
                                    status_line, content_length, body ? body : "");
    
    if (write(client_socket, response, response_len) < 0) {
        perror("write");
    }
}