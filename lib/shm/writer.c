#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "shm.h"
#include "hashmap.h"

int main(int argc, char* argv[]) {
    int to_write = 5;
    if (argc == 2) {
        to_write = atoi(argv[1]);
    }

    lock_shm();

    init_map(map_addr(), SHM_ELEMENT_COUNT);
    MapValue* map_value1 = add_int_value("bc", 104, map_addr(), SHM_ELEMENT_COUNT);
    MapValue* map_value2 = add_int_value("cB", -123, map_addr(), SHM_ELEMENT_COUNT);

    unlock_shm();

    printf("Map at %p, enetered at %p", map_addr(), map_value1);
    printf("Map at %p, enetered at %p", map_addr(), map_value2);
}
