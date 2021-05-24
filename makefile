include makefile.variable

all: install

.PHONY: libshm
libshm:
	cd src/c/ && make libshm.so

.PHONY: test
test: 
	cd test && make build_tests && make run_tests

.PHONY: reset_shm
reset_shm:
	rm -f /dev/shm/ROBOSHM

.PHONY: clean
clean: 
	rm -rf $(INCLUDE_INSTALL_PATH) $(BIN_INSTALL_PATH) $(PYTHON_INSTALL_PATH) /dev/shm/ROBOSHM
	cd test && make clean
	cd src/c && make clean

.PHONY: install
install: libshm
	mkdir -p $(INCLUDE_INSTALL_PATH) $(BIN_INSTALL_PATH) $(PYTHON_INSTALL_PATH)
	ln -s $(PROJECT_ROOT_DIR)/src/c/*.h $(INCLUDE_INSTALL_PATH)/
	ln -s $(PROJECT_ROOT_DIR)/src/c/libshm.so $(BIN_INSTALL_PATH)/libshm.so
	ln -s $(PROJECT_ROOT_DIR)/src/py/_libshm_wrapper.py $(PYTHON_INSTALL_PATH)/_libshm_wrapper.py
	ln -s $(PROJECT_ROOT_DIR)/src/py/shm.py $(PYTHON_INSTALL_PATH)/shm.py

.PHONY: all
