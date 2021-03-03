all: libshm.so

.PHONY: libshm.so
libshm.so: shm.c shm.h hashmap.c hashmap.h shm_hashmap.c shm_hashmap.h
	gcc -std=gnu99 -c -fPIC -Werror shm.c shm.h
	gcc -std=gnu99 -c -fPIC -Werror hashmap.c hashmap.h
	gcc -std=gnu99 -c -fPIC -Werror shm_hashmap.c shm_hashmap.h
	gcc -fPIC -shared -o libshm.so shm.o hashmap.o shm_hashmap.o
	rm -f /dev/shm/ROBOSHM

.PHONY: hashmap_test
hashmap_test: libshm.so
	g++ -o test/hashmap.t.out -I. -Itest/ test/hashmap.t.cc -L. -lshm -lrt -lpthread -lgtest -lgtest_main -Werror

.PHONY: run_hashmap_test
run_hashmap_test: test reset_shm
	LD_LIBRARY_PATH=. ./test/hashmap.t.out

.PHONY: shm_hashmap_test
shm_hashmap_test: libshm.so
	g++ -o test/shm_hashmap.t.out -I. -Itest/ test/shm_hashmap.t.cc -L. -lshm -lrt -lpthread -lgtest -lgtest_main -Werror

.PHONY: run_shm_hashmap_test
run_shm_hashmap_test: test reset_shm
	LD_LIBRARY_PATH=. ./test/shm_hashmap.t.out

.PHONY: test
test: hashmap_test shm_hashmap_test

.PHONY: run_test
run_test: run_hashmap_test run_shm_hashmap_test

.PHONY: reset_shm
reset_shm:
	rm -f /dev/shm/ROBOSHM

.PHONY: clean
clean: 
	rm -f *.out *.o *.so *.gch test/*.out /dev/shm/ROBOSHM

.PHONY: all
