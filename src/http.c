#define _GNU_SOURCE
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <gc.h>

#include "log.h"

int server_fd;
struct sockaddr_in server_addr;
const int PORT = 4080;
const int BUFFER_SIZE = 104857600;

void init_http_socket() {
    server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (server_fd < 0) {
        log_error("failed to set up web socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd,
             (struct sockaddr *) &server_addr,
             sizeof(server_addr)) < 0) {
        log_error("failed to bind socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        log_error("listen failure");
        exit(EXIT_FAILURE);
    }
}

void close_http_socket() {
    close(server_fd);
}

void build_response(
        const char *status,
        const char *buffer,
        char *response,
        size_t *response_len) {
    char *header = (char *) malloc(BUFFER_SIZE * sizeof(char));
    snprintf(header, BUFFER_SIZE,
             "HTTP/1.1 %s\r\n"
             "Content-Type: application/json\r\n"
             "\r\n"
             "\r\n"
             "%s",
             status,
             buffer);

    *response_len = 0;
    memcpy(response, header, strlen(header));
    *response_len += strlen(header);
    free(header);
}

void *handle_client(void *arg) {
    int client_fd = *((int *)arg);
    char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));

    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        char *response = (char *) malloc(BUFFER_SIZE * 2 * sizeof(char));
        size_t response_len;
        char *output = "";
        if (strncmp(buffer, "GET /players ", 13) == 0) {
            build_response("200 OK", output, response, &response_len);
        } else if (strncmp(buffer, "GET / ", 6) == 0) {
            build_response("200 OK", "I'm a teapot", response, &response_len);
        } else {
            build_response("404 Not Found", output, response, &response_len);
        }
        send(client_fd, response, response_len, 0);
        free(response);
    }
    close(client_fd);
    free(buffer);
    return NULL;
}

void poll_http() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int *client_fd = GC_MALLOC(sizeof(int));

    if ((*client_fd = accept4(server_fd,
                             (struct sockaddr *) &client_addr,
                             &client_addr_len,
                             SOCK_NONBLOCK)) < 0) {
        return;
    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, handle_client, (void *) client_fd);
    pthread_detach(thread_id);
}
