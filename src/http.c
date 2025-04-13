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
#include <jansson.h>

#include "merc.h"
#include "log.h"
#include "character.h"
#include "string_ext.h"

int server_fd;
struct sockaddr_in server_addr;
const int BUFFER_SIZE = 104857600;

void init_http_socket(const int port) {
    server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (server_fd < 0) {
        log_error("failed to set up web socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

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
    snprintf(response,
             BUFFER_SIZE,
             "HTTP/1.1 %s\r\n"
             "Content-Type: application/json\r\n"
             "Cache-Control: max-age=60\r\n"
             "\r\n"
             "%s",
             status,
             buffer);
    *response_len = strlen(response);
}

const char *players_endpoint() {
    json_auto_t *all_players = json_array();
    DESCRIPTOR_DATA *d;
    CHAR_DATA *wch;
    for (d = descriptor_list; d != NULL; d = d->next) {
        if (d->connected != CON_PLAYING) {
            continue;
        }
        wch = d->character;
        json_auto_t *player = json_object();
        char full_name[MAX_INPUT_LENGTH];
        if (wch->pcdata->surname) {
            sprintf(full_name, "%s %s", wch->name, wch->pcdata->surname);
        } else {
            sprintf(full_name, "%s", wch->name);
        }
        json_auto_t *name = json_string(full_name);
        json_object_set(player, "name", name);

        if (is_immortal(wch->level)) {
            const char *imm = get_immortal_role(wch->level);
            json_auto_t *json_imm = json_string(imm);
            json_object_set(player, "level", json_imm);
        } else {
            const char *class = class_table[wch->class].name;
            json_auto_t *json_class = json_string(class);
            json_object_set(player, "class", json_class);

            json_auto_t *race = json_string(race_table[wch->race].name);
            json_object_set(player, "race", race);

            json_auto_t *level = json_integer(wch->level);
            json_object_set(player, "level", level);
        }

        json_array_append(all_players, player);
    }
    return json_dumps(all_players, JSON_INDENT(4));
}

const char *build_endpoint() {
    json_auto_t *resp = json_object();
    json_auto_t *build = json_string(build_version);
    json_object_set(resp, "build", build);
    return json_dumps(resp, JSON_INDENT(4));
}

const char *races_endpoint() {
    json_auto_t *resp = json_array();
    for (int i = 0;; i++) {
        if (pc_race_table[i].name == NULL) {
            break;
        }
        json_auto_t *race = json_object();
        json_auto_t *name = json_string(pc_race_table[i].name);
        json_object_set(race, "name", name);
        json_auto_t *cp = json_integer(pc_race_table[i].points);
        json_object_set(race, "creationPoints", cp);
        json_auto_t *skills = json_array();
        int skill_count = sizeof(pc_race_table[i].skills) / sizeof(pc_race_table[i].skills[0]);
        for (int j = 0; j < skill_count; j++) {
            json_auto_t *skill = json_string(pc_race_table[i].skills[j]);
            json_array_append(skills, skill);
        }
        json_object_set(race, "skills", skills);
        json_auto_t *size = json_string(get_race_size(pc_race_table[i].size));
        json_object_set(race, "size", size);
        json_auto_t *stats = json_object();
        json_auto_t *stat_str = json_integer(pc_race_table[i].stats[0]);
        json_object_set(stats, "str", stat_str);
        json_auto_t *stat_int = json_integer(pc_race_table[i].stats[1]);
        json_object_set(stats, "int", stat_int);
        json_auto_t *stat_wis = json_integer(pc_race_table[i].stats[2]);
        json_object_set(stats, "wis", stat_wis);
        json_auto_t *stat_dex = json_integer(pc_race_table[i].stats[3]);
        json_object_set(stats, "dex", stat_dex);
        json_auto_t *stat_con = json_integer(pc_race_table[i].stats[4]);
        json_object_set(stats, "con", stat_con);
        json_auto_t *stat_cha = json_integer(pc_race_table[i].stats[5]);
        json_object_set(stats, "cha", stat_cha);
        json_object_set(race, "stats", stats);
        HELP_TRACKER *pTrack = help_tracks[0];
        while (pTrack != NULL) {
            if (str_cmp(pc_race_table[i].name, pTrack->keyword) == 0) {
                json_auto_t *help_text = json_string(replace_str(pTrack->help->text, "\n\r", ""));
                json_object_set(race, "description", help_text);
                break;
            }
            pTrack = pTrack->next;
        }
        json_array_append(resp, race);
    }
    return json_dumps(resp, JSON_INDENT(4));
}

void *handle_client(void *arg) {
    int client_fd = *((int *)arg);
    char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));

    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        char *response = (char *) malloc(BUFFER_SIZE * 2 * sizeof(char));
        size_t response_len;
        if (strncmp(buffer, "GET /players ", 13) == 0) {
            build_response("200 OK", players_endpoint(), response, &response_len);
        } else if (strncmp(buffer, "GET /build ", 11) == 0) {
            build_response("200 OK", build_endpoint(), response, &response_len);
        } else if (strncmp(buffer, "GET /races ", 11) == 0) {
            build_response("200 OK", races_endpoint(), response, &response_len);
        } else if (strncmp(buffer, "GET / ", 6) == 0) {
            build_response("200 OK", "", response, &response_len);
        } else {
            build_response("404 Not Found", "", response, &response_len);
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
    int client_fd = accept4(server_fd,
                            (struct sockaddr *) &client_addr,
                            &client_addr_len,
                            SOCK_NONBLOCK);
    if (client_fd > -1) {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *) &client_fd);
        pthread_detach(thread_id);
    }
}
