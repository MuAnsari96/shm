all: libshm.so

.PHONY: libshm.so
libshm.so: shm.c shm.h hashmap.c hashmap.h shm_hashmap.c shm_hashmap.h
	gcc -std=gnu99 -c -fPIC -Werror shm.c shm.h
	gcc -std=gnu99 -c -fPIC -Werror hashmap.c hashmap.h
	gcc -std=gnu99 -c -fPIC -Werror shm_hashmap.c shm_hashmap.h
	gcc -fPIC -shared -o libshm.so shm.o hashmap.o shm_hashmap.o
	rm -f /dev/shm/ROBOSHM

.PHONY: clean
clean: 
	rm -f *.out *.o *.so *.gch

.PHONY: all
