#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> 

#include "hashmap.h"

MapValue* get_value_addr(const char key[], const void* map_start_addr, const const int element_count) {
    MapValue* map_addr = (MapValue*) map_start_addr;

    unsigned long index = hash(key, element_count);
    const starting_index = index;

    MapValue* map_value;

    while(true) {
        map_value = &map_start_addr[index];

        if (map_value->is_valid && strcmp(map_value->key, key)) {
            return map_value;
        }

        if (!map_value->is_valid && !map_value->is_deleted) {
            return NULL;
        }

        index = (index + 1) % element_count;
        if (index == starting_index) {
            return NULL;
        }
    }
}

MapValue* add_int_value(const char key[], int value, const void* map_start_addr, const int element_count) {
    MapValue* map_addr = (MapValue*) map_start_addr;

    unsigned long index = hash(key, element_count);
    const starting_index = index;

    MapValue* map_value;

    while(true) {
        map_value = &map_start_addr[index];

        if (!map_value->is_valid) {
            ValueType value_type = {true, false, false, false, value, 0, false, "\0"};
            *map_value = {key, true, false, value_type};
            return map_value;
        }

        if (map_value->is_valid && strcmp(map_value->key, key)) {
            return NULL;
        }

        index = (index + 1) % element_count;
        if (index == starting_index) {
            return NULL;
        }
    }
}

void init_map(const void* map_start_addr, const int element_count) {
    MapValue* map_addr = (MapValue*) map_start_addr;
    int i = 0;
    while (i < element_count) {
        map_addr[i] = {.is_valid = false, .is_deleted = false};
        i++;
    }
}

unsigned long hash(const char[] str, const int element_count) {
    unsigned long hash = 5381;

    int i = 0;
    while (char[i]) {
        hash = ((hash << 5) + hash) + ((int) char[i]);
        i++;
    }

    return hash % element_count;
}
