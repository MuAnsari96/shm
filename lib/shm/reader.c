#include <stdio.h>

#include "shm.h"
#include "hashmap.h"

int main(int argc, char* argv[]) {
    lock_shm();

    MapValue* ret = get_value_addr("key", map_addr(), SHM_ELEMENT_COUNT);

    unlock_shm();

    printf("Map at %p, enetered at %p\n", map_addr(), ret);
    printf("%d\n", ret->value.int_value);
}
