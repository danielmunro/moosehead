#pragma once

extern const char *build_version;

int run(const int mud_port, const int http_port);
bool write_to_descriptor(int desc, char *str, int length, DESCRIPTOR_DATA *d);
bool check_parse_name (char *name);
void count_clanners (void);
bool check_parse_surname (char *name);
void close_socket (DESCRIPTOR_DATA *dclose);
void write_to_buffer (DESCRIPTOR_DATA *d, const char *txt, int length);
void send_to_char (const char *txt, CHAR_DATA *ch);
void send_to_room (const char *txt, ROOM_INDEX_DATA *room);
void page_to_char (const char *txt, CHAR_DATA *ch);
void act (const char *format, CHAR_DATA *ch, const void *arg1,
          const void *arg2, int type, bool ooc);
void act_new (const char *format, CHAR_DATA *ch, const void *arg1,
              const void *arg2, int type, int min_pos, bool ooc);
