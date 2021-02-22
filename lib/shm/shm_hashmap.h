#ifndef SHM_HASHMAP_H
#define SHM_HASHMAP_H

#include <stdbool.h>

// SHM INTERFACE
// This takes a properly formatted buffer, and provides the actual APIs we want 
// to use it as a functional hashmap/tree/whatever

void init_shm();

// TODO Change workflow from this to add, update, set, get, contains 
int get_int_value(const char key[]);
bool set_int_value(const char key[], int value);
bool register_int_value(const char key[], int value);

#endif
