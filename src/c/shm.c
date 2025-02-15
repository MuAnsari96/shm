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
#include "hashmap.h"

const char* SHM_NAME = "/ROBOSHM";
const int SHM_ELEMENT_COUNT = 32000;

static int shm_fd_ = -1;
static void* shm_addr_p = NULL;

int shm_effective_size() {
    return SHM_ELEMENT_COUNT*sizeof(MapValue) + sizeof(pthread_mutex_t) + sizeof(pthread_mutexattr_t);
}

void* shm_addr() {

    if (shm_addr_p) {
        return shm_addr_p;
    }

    int lockfile = open("/tmp/roboshm.init.lock", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    if (lockfile == -1) {
        printf("Encountered error acquiring lockfile. Errcode %d\n", errno);
    }
    fchmod(lockfile, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    flock(lockfile, LOCK_EX);

    shm_fd_ = shm_open(SHM_NAME, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    if (shm_fd_ != -1) { 
        fchmod(shm_fd_, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
        // TODO Factor out into an init
        int rc = ftruncate(shm_fd_, shm_effective_size());
        if (rc == -1) {
            return NULL;
        }

        shm_addr_p = mmap(NULL, shm_effective_size(), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
        if (shm_addr_p == MAP_FAILED) {
            printf("Encountered error mmap'ing shm. Errcode: %d\n", errno);
            return NULL;
        }
        
        pthread_mutex_t* mutex = (pthread_mutex_t*) shm_addr_p;
        pthread_mutexattr_t* mutexattr = (pthread_mutexattr_t*) (((char*)shm_addr_p) + sizeof(pthread_mutex_t));
        pthread_mutexattr_init(mutexattr);
        pthread_mutexattr_setpshared(mutexattr, PTHREAD_PROCESS_SHARED);
        pthread_mutexattr_setrobust(mutexattr, PTHREAD_MUTEX_ROBUST);
        pthread_mutex_init(mutex, mutexattr);

    }
    else if (errno == EEXIST) {
        shm_fd_ = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
        if (shm_fd_ == -1) {
            printf("Encountered error openinng shm file. Errcode: %d\n", errno);
            return NULL;
        }

        shm_addr_p = mmap(NULL, shm_effective_size(), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
        if (shm_addr_p == MAP_FAILED) {
            printf("Encountered error mmap'ing shm. Errcode: %d\n", errno);
            return NULL;
        }
        printf("Shm already exists, using that instance\n");
    }
    else {
        printf("Encountered fd unknown error %d\n", errno);
        return NULL;
    }

    flock(lockfile, LOCK_UN);
    return shm_addr_p;
}

void* map_addr() {
    const int offset = sizeof(pthread_mutex_t) + sizeof(pthread_mutexattr_t);
    return (((char*)shm_addr()) + offset);
}

void lock_shm() {
    int* addr = (int*)shm_addr();
    pthread_mutex_lock((pthread_mutex_t*)addr);
}

void unlock_shm() {
    int* addr = (int*)shm_addr();
    pthread_mutex_unlock((pthread_mutex_t*)addr);
}

void shm_init() {
    init_map(shm_addr(), SHM_ELEMENT_COUNT);
}

void shm_close() {
    munmap(shm_addr(), shm_effective_size());
    close(shm_fd_);
    shm_unlink(SHM_NAME);
    shm_addr_p = NULL;
}
