#ifndef SHM_HASHMAP_H
#define SHM_HASHMAP_H

#include <stdbool.h>

#include "hashmap.h"

// SHM INTERFACE
// This takes a properly formatted buffer, and provides the actual APIs we want 
// to use it as a functional hashmap/tree/whatever

// get
MapValue* get_map_value(const char key[]);

// set
bool set_int_value(const char key[], const int value);
bool set_float_value(const char key[], const float value);
bool set_bool_value(const char key[], const bool value);
bool set_char_value(const char key[], const char value[]);

// contains
bool contains_key(const char key[]);

// delete
bool delete_key(const char key[]);

int get_int_value(const char key[]);
bool set_int_value(const char key[], int value);
bool register_int_value(const char key[], int value);

#endif
