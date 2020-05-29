#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <unistd.h>

#include "shm.h"

const char* SHM_NAME = "/ROBOSHM";
const int SHM_SIZE = 32000;
const int data_offset = sizeof(pthread_mutex_t) + sizeof(pthread_mutexattr_t);
static int shm_fd_ = -1;

void* shm_addr() {
    static void* shm_addr = NULL;

    if (shm_addr) {
        return shm_addr;
    }

    int lockfile = open("/tmp/roboshm.init.lock", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (lockfile == -1) {
        printf("Encountered error acquiring lock. Errcode %d\n", errno);
    }
    flock(lockfile, LOCK_EX);

    printf("LOCKED FILE\n");

    shm_fd_ = shm_open(SHM_NAME, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
    if (shm_fd_ != -1) { 
        printf("Initing shm...\n");

        int rc = ftruncate(shm_fd_, SHM_SIZE);
        if (rc == -1) {
            return NULL;
        }

        shm_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
        
        printf("Making my mutex");

        pthread_mutex_t* mutex = (pthread_mutex_t*) shm_addr;
        pthread_mutexattr_t* mutexattr = (pthread_mutexattr_t*) (shm_addr + sizeof(pthread_mutex_t));
        pthread_mutexattr_init(mutexattr);
        pthread_mutexattr_setpshared(mutexattr, PTHREAD_PROCESS_SHARED);
        pthread_mutexattr_setrobust(mutexattr, PTHREAD_MUTEX_ROBUST);
        pthread_mutex_init(mutex, mutexattr);

        printf("Done with stuff, spinning\n");
    }
    else if (errno == EEXIST) {
        shm_fd_ = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

        shm_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
        printf("Shm already exists, using that instance\n");
    }
    else {
        printf("Encountered fd unknown error %d\n", errno);
        return NULL;
    }

    flock(lockfile, LOCK_UN);
    printf("Unlocked\n");
    return shm_addr;
}

bool shm_place(int val) {
    int* addr = (int*)shm_addr();
    if (!addr) { 
        return false;
    }
    printf("taking lock\n");
    pthread_mutex_lock((pthread_mutex_t*)addr);
    printf("taken lock\n");
    addr[1000] = val;
    printf("Placing...\n");
    sleep(10);
    pthread_mutex_unlock((pthread_mutex_t*)addr);
    printf("released lock\n");
    return true;
}

int shm_get() {
    int* addr = (int*)shm_addr();
    if (!addr) {
        return -1;
    }
    int ret;
    printf("taking lock\n");
    pthread_mutex_lock((pthread_mutex_t*)addr);
    printf("taken lock\n");
    ret = addr[1000];
    sleep(10);
    pthread_mutex_unlock((pthread_mutex_t*)addr);
    printf("released lock\n");
    return ret;
}

void shm_close() {
    munmap(shm_addr(), SHM_SIZE);
    close(shm_fd_);
    shm_unlink(SHM_NAME);
}
