#ifndef MOOSEHEAD_COMM_H
#define MOOSEHEAD_COMM_H

extern const char *build_version;

int run(const int mud_port, const int http_port);
bool write_to_descriptor(int desc, char *str, int length, DESCRIPTOR_DATA *d);
bool check_parse_name (char *name);
void count_clanners (void);
bool check_parse_surname (char *name);
void close_socket (DESCRIPTOR_DATA *dclose);
void write_to_buffer (DESCRIPTOR_DATA *d, const char *txt, int length);

#endif //MOOSEHEAD_COMM_H
