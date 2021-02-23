#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "shm.h"
#include "hashmap.h"
#include "shm_hashmap.h"

int main(int argc, char* argv[]) {
    int to_write = 5;
    if (argc == 2) {
        to_write = atoi(argv[1]);
    }

    init_map(map_addr(), SHM_ELEMENT_COUNT);
    set_int_value("bc", 104);
    set_int_value("bc", 105);
    set_int_value("cB", -123);
}
