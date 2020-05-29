#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "shm.h"

int main(int argc, char* argv[]) {
    int to_write = 5;
    if (argc == 2) {
        to_write = atoi(argv[1]);
    }
    bool x = shm_place(to_write);
    if (!x) {
        printf("Didnt work bro...");
    }
}
