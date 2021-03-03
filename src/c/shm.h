#ifndef SHM_H
#define SHM_H

#include <stdbool.h>

// GLOBAL SHM STUFF
// Right now, the responsibilities of this module are to set up the memory area assuming
// a set layout, provide basic accessors to the different regions and perform global ops

extern const char* SHM_NAME;
extern const int SHM_ELEMENT_COUNT;

void lock_shm();
void unlock_shm();

// TODO Groups tree addr
void* map_addr();

void shm_init();
void shm_close();

#endif
