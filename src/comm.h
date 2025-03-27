#ifndef MOOSEHEAD_COMM_H
#define MOOSEHEAD_COMM_H

int run(int port);
bool write_to_descriptor(int desc, char *str, int length, DESCRIPTOR_DATA *d);

#endif //MOOSEHEAD_COMM_H
