all: writer reader

.PHONY: writer
writer: libshm.so writer.c
	gcc -o writer -I. writer.c -L. -lshm -lrt -lpthread -Werror

.PHONY: reader
reader: libshm.so reader.c
	gcc -o reader -I./ reader.c -L./ -lshm -lrt -lpthread -Werror

.PHONY: libshm.so
libshm.so: shm.c shm.h hashmap.c hashmap.h shm_hashmap.c shm_hashmap.h
	gcc -std=gnu99 -c -fPIC -Werror shm.c shm.h
	gcc -std=gnu99 -c -fPIC -Werror hashmap.c hashmap.h
	gcc -std=gnu99 -c -fPIC -Werror shm_hashmap.c shm_hashmap.h
	gcc -fPIC -shared -o libshm.so shm.o hashmap.o shm_hashmap.o
	rm -f /dev/shm/ROBOSHM

.PHONY: run_reader
run_reader:
	LD_LIBRARY_PATH=. ./reader

.PHONY: run_writer
run_writer:
	LD_LIBRARY_PATH=. ./writer

.PHONY: full_run_reader
full_run_reader: reader
	LD_LIBRARY_PATH=. ./reader

.PHONY: full_run_writer
full_run_writer: writer
	LD_LIBRARY_PATH=. ./writer


.PHONY: clean
clean: 
	rm -f writer reader *.o *.so *.gch

.PHONY: all
