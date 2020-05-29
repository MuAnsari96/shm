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
static int shm_fd_ = -1;

int shm_fd() {
    if (shm_fd_ != -1) {
        return shm_fd_;
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
        printf("Done with stuff, spinning\n");
        sleep(10);
    }
    else if (errno == EEXIST) {
        shm_fd_ = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        printf("Shm already exists, using that instance\n");
    }
    else {
        printf("Encountered fd unknown error %d\n", errno);
    }

    flock(lockfile, LOCK_UN);
    printf("Unlocked\n");
    return shm_fd_;
}

void* shm_addr() {
    static void* shm_addr = NULL;

    if (shm_addr) {
        return shm_addr;
    }

    int fd = shm_fd();
    int rc = ftruncate(fd, SHM_SIZE);
    if (rc == -1) {
        return NULL;
    }

    shm_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    return shm_addr;
}

bool shm_place(int val) {
    int* addr = (int*)shm_addr();
    if (!addr) { 
        return false;
    }
    addr[0] = val;
    printf("Placing...\n");
    return true;
}

int shm_get() {
    int* addr = (int*)shm_addr();
    if (!addr) {
        return -1;
    }
    return addr[0];
}

void shm_close() {
    munmap(shm_addr(), SHM_SIZE);
    close(shm_fd_);
    shm_unlink(SHM_NAME);
}
