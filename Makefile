
export TOPDIR    := $(shell pwd)
export BUILD_DIR := $(TOPDIR)/build
export PREFIX    ?= $(TOPDIR)/build

export CC        ?= gcc
export CFLAGS    := -std=c++17 -I$(BUILD_DIR)/include

.PHONY: build

build: test install

test: install
	$(info [-] Runnning Tests)

install: prepare
	$(info [+] Installing Headers)
	cp -r $(TOPDIR)/include $(PREFIX)/include/asyncpp

prepare:
	$(info [+] Creating directories)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(PREFIX)
	rm -rf $(PREFIX)/include/asyncpp
	mkdir -p $(PREFIX)/include

$(V).SILENT:
