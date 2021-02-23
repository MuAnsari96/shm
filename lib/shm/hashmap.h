#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

// GENERIC HASHAMP STUFF
// This module provides a generic API for hashmap operations given a memory buffer we want to use

// TODO Add rw lock in value
typedef struct ValueType {
    bool is_int;
    bool is_float;
    bool is_bool;
    bool is_char;

    // TODO Add support for *
    int int_value;
    float float_value;
    bool bool_value;
    char char_value[8];
} ValueType;

typedef struct MapValue {
    char key[16];
    bool is_valid;
    bool is_deleted;
    ValueType value;
} MapValue;

// init
MapValue* init_int_map_var(const char key[], const int value, const void* map_start_addr, const int element_count);
MapValue* init_float_map_var(const char key[], const float value, const void* map_start_addr, const int element_count);
MapValue* init_bool_map_var(const char key[], const bool value, const void* map_start_addr, const int element_count);
MapValue* init_char_map_var(const char key[], const char value[], const void* map_start_addr, const int element_count);

// get
MapValue* get_map_var(const char key[], const void* map_start_addr, const int element_count);

// delete
bool delete_map_var(const char key[], const void* map_start_addr, const int element_count);

void init_map(const void* map_start_addr, const int element_count);
unsigned long hash(const char str[], const int element_count);

#endif
