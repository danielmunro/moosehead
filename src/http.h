#ifndef MOOSEHEAD_WEB_H
#define MOOSEHEAD_WEB_H

void init_http_socket(const int port);
void close_http_socket();
void *poll_http(void *arg);

#endif //MOOSEHEAD_WEB_H
