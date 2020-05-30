#ifndef SHM_H
#define SHM_H

#include <stdbool.h>

const char* SHM_NAME = "/ROBOSHM";
const int SHM_ELEMENT_COUNT = 32000;

void lock_shm();
void unlock_shm();

void* map_addr();

void shm_close();

#endif
