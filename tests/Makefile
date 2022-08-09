# asyncpp tests

TOPDIR    ?= ..
BUILD_DIR ?= $(TOPDIR)/build

.PHONY: build run

run: build
	echo
	$(TOPDIR)/tests/run

build:
	for file in *.cc; do \
		$(CXX) $(CXXFLAGS) $$file -o $(BUILD_DIR)/bin/$${file%.*}; \
	done
