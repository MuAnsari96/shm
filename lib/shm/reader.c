#include <stdio.h>

#include "shm.h"
#include "hashmap.h"
#include "shm_hashmap.h"

int main(int argc, char* argv[]) {
    MapValue* ret1 = get_map_value("bc");
    MapValue* ret2 = get_map_value("cB");

    printf("Map at %p, enetered at %p\n", map_addr(), ret1);
    printf("%d\n", ret1->value.int_value);
    printf("Map at %p, enetered at %p\n", map_addr(), ret2);
    printf("%d\n", ret2->value.int_value);
}
