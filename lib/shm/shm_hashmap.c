#include <stddef.h>

#include "hashmap.h"
#include "shm.h"

// get
MapValue* get_map_value(const char key[]) {
    MapValue* value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
    return value;
}

// set
bool set_int_value(const char key[], const int value) {
    MapValue* map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);

    if (map_value) {
        if (!map_value->value.is_int) {
            return false;
        }
        map_value->value.int_value = value;
        return true;
    }

    lock_shm();
    map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
    if (!map_value) {
        map_value = init_int_map_var(key, 0, map_addr(), SHM_ELEMENT_COUNT);
    }
    unlock_shm();

    if (map_value) {
        if (!map_value->value.is_int) {
            return false;
        }
        map_value->value.int_value = value;
        return true;
    }

    return false;
}

bool set_float_value(const char key[], const float value) {
    MapValue* map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);

    if (map_value) {
        if (!map_value->value.is_float) {
            return false;
        }
        map_value->value.float_value = value;
        return true;
    }

    lock_shm();
    map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
    if (!map_value) {
        map_value = init_float_map_var(key, 0., map_addr(), SHM_ELEMENT_COUNT);
    }
    unlock_shm();

    if (map_value) {
        if (!map_value->value.is_float) {
            return false;
        }
        map_value->value.float_value = value;
        return true;
    }

    return false;
}

bool set_bool_value(const char key[], const bool value) {
    MapValue* map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);

    if (map_value) {
        if (!map_value->value.is_bool) {
            return false;
        }
        map_value->value.bool_value = value;
        return true;
    }

    lock_shm();
    map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
    if (!map_value) {
        map_value = init_bool_map_var(key, false, map_addr(), SHM_ELEMENT_COUNT);
    }
    unlock_shm();

    if (map_value) {
        if (!map_value->value.is_bool) {
            return false;
        }
        map_value->value.bool_value = value;
        return true;
    }

    return false;
}

bool set_char_value(const char key[], const char value[]) {
    MapValue* map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);

    if (map_value) {
        if (!map_value->value.is_char) {
            return false;
        }
        // TODO Bad, should be strcpy
        //map_value->value.char_value = value;
        return true;
    }

    lock_shm();
    map_value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
    if (!map_value) {
        map_value = init_char_map_var(key, "\0", map_addr(), SHM_ELEMENT_COUNT);
    }
    unlock_shm();

    if (map_value) {
        if (!map_value->value.is_char) {
            return false;
        }
        // TODO Bad, should be strcpy
        //map_value->value.char_value = value;
        return true;
    }

    return false;
}

// contains
bool contains_key(const char key[]) {
    MapValue* value = get_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
    return value != NULL;
}

// delete
bool delete_key(const char key[]) {
    return delete_map_var(key, map_addr(), SHM_ELEMENT_COUNT);
}
