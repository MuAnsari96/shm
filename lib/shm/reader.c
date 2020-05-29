#include <stdio.h>

#include "shm.h"

int main(int argc, char* argv[]) {
    printf("%d\n", shm_get());
}
