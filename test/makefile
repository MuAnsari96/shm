include ../makefile.variable

all: run_tests

.PHONY: reset_shm
reset_shm:
	rm -f /dev/shm/ROBOSHM

.PHONY: hashmap_test
hashmap_test:
	g++ -o hashmap.t.out -I$(INCLUDE_INSTALL_PATH) hashmap.t.cc -L$(BIN_INSTALL_PATH) -lshm -lrt -lpthread -lgtest -lgtest_main -Werror

.PHONY: run_hashmap_test
run_hashmap_test: reset_shm
	LD_LIBRARY_PATH=$(BIN_INSTALL_PATH) ./hashmap.t.out

.PHONY: shm_hashmap_test
shm_hashmap_test:
	g++ -o shm_hashmap.t.out -I$(INCLUDE_INSTALL_PATH) -I. shm_hashmap.t.cc -L$(BIN_INSTALL_PATH) -lshm -lrt -lpthread -lgtest -lgtest_main -Werror

.PHONY: run_shm_hashmap_test
run_shm_hashmap_test: reset_shm
	LD_LIBRARY_PATH=$(BIN_INSTALL_PATH) ./shm_hashmap.t.out

.PHONY: build_tests
build_tests: hashmap_test shm_hashmap_test

.PHONY: run_test
run_tests: run_hashmap_test run_shm_hashmap_test

.PHONY: clean
clean: 
	rm -f *.out *.o *.so *.gch 

.PHONY: run_tests
