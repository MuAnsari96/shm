#ifndef SHM_HASHMAP_H
#define SHM_HASHMAP_H

#include <stdbool.h>

void init_shm();

int get_int_value(const char key[]);
bool set_int_value(const char key[], int value);
bool register_int_value(const char key[], int value);

#endif
