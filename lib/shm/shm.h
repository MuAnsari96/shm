#ifndef SHM_H
#define SHM_H

#include <stdbool.h>

bool shm_place(int val);
int shm_get();

void shm_close();

#endif
