#include "hashmap.h"
#include "shm.h"

int get_int_value(const char key[]) {
    MapValue* value = get_value_addr(key, map_addr(), SHM_ELEMENT_COUNT);
    return value->value.int_value;
}

bool set_int_value(const char key[], int value) {
    MapValue* map_value = get_value_addr(key, map_addr(), SHM_ELEMENT_COUNT);
    map_value->value.int_value = value;
    return true;
}

bool register_int_value(const char key[]) {
    MapValue* map_value = add_int_value(key, 0, map_addr(), SHM_ELEMENT_COUNT);
    return true;
}

