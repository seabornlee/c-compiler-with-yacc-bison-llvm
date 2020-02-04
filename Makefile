BUILD_DIR = build
TEST_DIR = $(BUILD_DIR)/test

.PHONY: test
test: build
	cd $(TEST_DIR) && ctest -V

build: checkout
	mkdir $(BUILD_DIR) && cd $(BUILD_DIR) && cmake .. && make all

check: checkout
	cppcheck --error-exitcode=1 -i lib -i build -i cmake-build-debug .

checkout:
	git submodule init && git submodule update

clean:
	rm -r $(BUILD_DIR)
