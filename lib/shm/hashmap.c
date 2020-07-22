#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h> 

#include "hashmap.h"

MapValue* get_value_addr(const char key[], const void* map_start_addr, const const int element_count) {
    MapValue* map_addr = (MapValue*) map_start_addr;

    unsigned long index = hash(key, element_count);
    const unsigned long starting_index = index;

    MapValue* map_value;

    while(true) {
        map_value = &map_addr[index];

        if (map_value->is_valid && (strcmp(map_value->key, key) == 0)) {
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
    const unsigned long starting_index = index;

    MapValue* map_value;

    while(true) {
        map_value = &map_addr[index];

        if (!map_value->is_valid) {
            ValueType value_type = {true, false, false, false, value, 0, false, "\0"};
            strcpy(map_value->key, key);
            map_value->is_valid = true;
            map_value->is_deleted = false;
            map_value->value = value_type;
            return map_value;
        }

        if (map_value->is_valid && (strcmp(map_value->key, key) == 0)) {
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
        map_addr[i].is_valid = false;
        map_addr[i].is_deleted = false;
        i++;
    }
}

unsigned long hash(const char str[], const int element_count) {
    unsigned long hash = 5381;

    int i = 0;
    while (str[i]) {
        hash = ((hash << 5) + hash) + ((int) str[i]);
        i++;
    }

    printf("%lu is the hash\n", hash % element_count);
    return hash % element_count;
}
