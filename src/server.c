#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "request.h"
#include "response.h"
#include "utils.h"

#define PORT 8080

void start_server() {
    int server_fd, new_socket;
}