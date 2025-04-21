#ifndef MOOSEHEAD_COMM_H
#define MOOSEHEAD_COMM_H

extern const char *build_version;

int run(const int mud_port, const int http_port);
bool write_to_descriptor(int desc, char *str, int length, DESCRIPTOR_DATA *d);
bool check_parse_name (char *name);
void count_clanners (void);
bool check_parse_surname (char *name);

#endif //MOOSEHEAD_COMM_H
