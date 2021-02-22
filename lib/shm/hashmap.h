#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

// GENERIC HASHAMP STUFF
// This module provides a generic API for hashmap operations given a memory buffer we want to use

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


// TODO Change workflow from this to add, update, set, get, contains 
MapValue* get_value_addr(const char key[], const void* map_start_addr, const int element_count);
MapValue* add_int_value(const char key[], int value, const void* map_start_addr, const int element_count);
// TODO Add support for other primitives
void init_map(const void* map_start_addr, const int element_count);
unsigned long hash(const char str[], const int element_count);

#endif
