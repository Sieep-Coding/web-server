#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "response.h"
#include "request.h"
#include "utils.h"

void handle_request(int client_socket) {
    char buffer[4096];
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("read");
        return;
    }

    buffer[bytes_read] = '\0';

    Request *request = parse_request(buffer, bytes_read);
    if (request == NULL) {
        send_response(client_socket, 400, "Bad Request", NULL, 0);
        return;
    }

    if (strcmp(request->method, "GET") == 0) {
        char *file_path = request->path + 1;
        if (file_path[0] == '\0') {
            file_path = "www/index.html";
        }

        struct stat file_stat;
        if (stat(file_path, &file_stat) < 0) {
            send_response(client_socket, 404, "Not Found", NULL, 0);
            free_request(request);
            return;
        }

        FILE *file = fopen(file_path, "r");
        if (file == NULL) {
            send_response(client_socket, 500, "Internal Server Error", NULL, 0);
            free_request(request);
            return;
        }

        char *content = malloc(file_stat.st_size + 1);
        if (content == NULL) {
            send_response(client_socket, 500, "Internal Server Error", NULL, 0);
            fclose(file);
            free_request(request);
            return;
        }

        size_t bytes_read = fread(content, 1, file_stat.st_size, file);
        if (bytes_read != (size_t)file_stat.st_size) {
            send_response(client_socket, 500, "Internal Server Error", NULL, 0);
            fclose(file);
            free(content);
            free_request(request);
            return;
        }

        content[bytes_read] = '\0';
        send_response(client_socket, 200, "OK", content, bytes_read);

        fclose(file);
        free(content);
        free_request(request);
    } else {
        send_response(client_socket, 501, "Not Implemented", NULL, 0);
        free_request(request);
    }
}