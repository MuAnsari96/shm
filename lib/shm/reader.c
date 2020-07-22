#include <stdio.h>

#include "shm.h"
#include "hashmap.h"

int main(int argc, char* argv[]) {
    lock_shm();

    MapValue* ret1 = get_value_addr("bc", map_addr(), SHM_ELEMENT_COUNT);
    MapValue* ret2 = get_value_addr("cB", map_addr(), SHM_ELEMENT_COUNT);

    unlock_shm();

    printf("Map at %p, enetered at %p\n", map_addr(), ret1);
    printf("%d\n", ret1->value.int_value);
    printf("Map at %p, enetered at %p\n", map_addr(), ret2);
    printf("%d\n", ret2->value.int_value);
}
