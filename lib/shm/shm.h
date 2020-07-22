#ifndef SHM_H
#define SHM_H

#include <stdbool.h>

extern const char* SHM_NAME;
extern const int SHM_ELEMENT_COUNT;

void lock_shm();
void unlock_shm();

void* map_addr();

void shm_close();

#endif
