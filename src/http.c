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
#include <regex.h>
#include <yuarel.h>

#include "merc.h"
#include "log.h"
#include "lookup.h"

int server_fd;
struct sockaddr_in server_addr;
const int BUFFER_SIZE = 104857600;

char *index_endpoint(struct yuarel url);
char *players_endpoint(struct yuarel url);
char *races_endpoint(struct yuarel url);
char *build_endpoint(struct yuarel url);
char *classes_endpoint(struct yuarel url);
char *help_endpoint(struct yuarel url);

typedef struct {
    char *method;
    char *path;
    char *(*response)(struct yuarel url);
} Endpoint;

Endpoint endpoints[] = {
        {"GET", "", index_endpoint},
        {"GET", "players", players_endpoint},
        {"GET", "races", races_endpoint},
        {"GET", "build", build_endpoint},
        {"GET", "classes", classes_endpoint},
        {"GET", "help", help_endpoint}
};

void init_http_socket(const int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

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

char *index_endpoint(struct yuarel url) {
    json_auto_t *response = json_object();
    int endpoint_count = sizeof(endpoints) / sizeof(endpoints[0]);
    json_auto_t *endpoint_response = json_array();
    char path[MAX_INPUT_LENGTH];
    for (int i = 0; i < endpoint_count; i++) {
        json_auto_t *one_endpoint = json_object();
        json_auto_t *one_method = json_string(endpoints[i].method);
        json_object_set(one_endpoint, "method", one_method);
        sprintf(path, "/%s", endpoints[i].path);
        json_auto_t *one_path = json_string(path);
        json_object_set(one_endpoint, "path", one_path);
        json_array_append(endpoint_response, one_endpoint);
    }
    json_object_set(response, "endpoints", endpoint_response);
    return json_dumps(response, JSON_INDENT(4));
}

char *help_endpoint(struct yuarel url) {
    struct yuarel_param params[1];
    json_auto_t *response = json_object();
    bool found = false;

    if (yuarel_parse_query(url.query, '&', params, 1) < 0) {
        json_auto_t *error_text = json_string("Unable to parse query");
        json_object_set(response, "error", error_text);
        return json_dumps(response, JSON_INDENT(4));
    }

    if (strcmp(params[0].key, "query") != 0) {
        json_auto_t *error_text = json_string("Must have only one query parameter: `query`");
        json_object_set(response, "error", error_text);
        return json_dumps(response, JSON_INDENT(4));
    }

    for (HELP_TRACKER *pTrack = help_tracks[0]; pTrack != NULL; pTrack = pTrack->next) {
        if (str_cmp(params[0].val, pTrack->keyword) == 0 && pTrack->help->level <= LEVEL_HERO) {
            json_auto_t *help_text = json_string(pTrack->help->text);
            json_object_set(response, "help", help_text);
            found = true;
            break;
        }
    }

    if (!found) {
        json_auto_t *error_text = json_string("No help topic found");
        json_object_set(response, "error", error_text);
    }

    return json_dumps(response, JSON_INDENT(4));
}

char *classes_endpoint(struct yuarel url) {
    json_auto_t *classes = json_array();
    for (int i = 0; strcmp(class_table[i].name, "null") != 0; i++) {
        json_auto_t *class = json_object();
        json_auto_t *name = json_string(class_table[i].name);
        json_object_set(class, "name", name);
        json_auto_t *primary = json_string(stat_name_lookup(class_table[i].attr_prime));
        json_object_set(class, "primary_attribute", primary);
        json_auto_t *secondary = json_string(stat_name_lookup(class_table[i].attr_second));
        json_object_set(class, "secondary_attribute", secondary);
        json_auto_t *weapon = json_string(weapon_name_lookup(class_table[i].weapon));
        json_object_set(class, "starting_weapon", weapon);
        for (HELP_TRACKER *pTrack = help_tracks[0]; pTrack != NULL; pTrack = pTrack->next) {
            if (str_cmp(class_table[i].name, pTrack->keyword) == 0) {
                json_auto_t *help_text = json_string(pTrack->help->text);
                json_object_set(class, "description", help_text);
                break;
            }
        }
        json_array_append(classes, class);
    }
    return json_dumps(classes, JSON_INDENT(4));
}

char *players_endpoint(struct yuarel url) {
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
            const char *imm = immortal_role_name_lookup(wch->level);
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

char *build_endpoint(struct yuarel url) {
    json_auto_t *resp = json_object();
    json_auto_t *build = json_string(build_version);
    json_object_set(resp, "build", build);
    return json_dumps(resp, JSON_INDENT(4));
}

char *races_endpoint(struct yuarel url) {
    json_auto_t *resp = json_array();
    for (int i = 1; race_table[i].name != NULL; i++) {
        if (!race_table[i].pc_race) {
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
        json_auto_t *size = json_string(size_name_lookup(pc_race_table[i].size));
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
        for (HELP_TRACKER *pTrack = help_tracks[0]; pTrack != NULL; pTrack = pTrack->next) {
            if (str_cmp(pc_race_table[i].name, pTrack->keyword) == 0) {
                json_auto_t *help_text = json_string(pTrack->help->text);
                json_object_set(race, "description", help_text);
                break;
            }
        }
        json_array_append(resp, race);
    }
    return json_dumps(resp, JSON_INDENT(4));
}

void handle_client(int client_fd) {
    char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received > 0) {
        char *response = (char *) malloc(BUFFER_SIZE * 2 * sizeof(char));
        size_t response_len;
        char *output = "";
        regex_t regex;
        regcomp(&regex, "^([A-Z]+)(\\s+)(.*)(\\s+)(HTTP\\/)([0-9].[0-9])", REG_EXTENDED);
        regmatch_t matches[4];
        if (regexec(&regex, buffer, 4, matches, 0) == 0) {
            int method_len = matches[1].rm_eo - matches[1].rm_so;
            char method[method_len + 1];
            strncpy(method, &buffer[matches[1].rm_so], method_len);
            method[method_len] = '\0';
            int path_len = matches[3].rm_eo - matches[3].rm_so;
            char path[path_len + 1];
            strncpy(path, &buffer[matches[3].rm_so], path_len);
            path[path_len] = '\0';
            struct yuarel url;
            if (yuarel_parse(&url, path) < 0) {
                sprintf(log_buf, "invalid url requested :: %s", path);
                log_info(log_buf);
            } else {
                int endpoint_count = sizeof(endpoints) / sizeof(endpoints[0]);
                bool found = false;
                for (int i = 0; i < endpoint_count; i++) {
                    if (strcmp(method, endpoints[i].method) == 0
                        && strcmp(url.path, endpoints[i].path) == 0) {
                        output = endpoints[i].response(url);
                        found = true;
                    } else if (strcmp(method, "HEAD") == 0
                               && strcmp(url.path, endpoints[i].path) == 0) {
                        found = true;
                    }
                }

                if (found) {
                    build_response("200 OK", output, response, &response_len);
                } else {
                    build_response("404 Not Found", "", response, &response_len);
                }

                send(client_fd, response, response_len, 0);
            }
        }

        free(response);
    }
    close(client_fd);
    free(buffer);
}

void *_poll_http(void *arg) {
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd,
                                (struct sockaddr *) &client_addr,
                                &client_addr_len);
        if (client_fd > -1) {
            handle_client(client_fd);
        }
    }
    return NULL;
}

void start_http_thread(int port) {
    init_http_socket(port);

    pthread_t http_thread;
    pthread_create(&http_thread, NULL, _poll_http, NULL);
    pthread_detach(http_thread);
}
