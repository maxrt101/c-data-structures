# c-data-structures (cds)

export TOPDIR := $(shell pwd)
export PREFIX ?= $(TOPDIR)/build
export BUILD  := $(TOPDIR)/build
export CC     := gcc
export AR     := ar
export CFLAGS := -std=c11 -I$(BUILD)/include

TARGET := $(PREFIX)/lib/libcds.a
SRC    := src/memory.c \
          src/clist/clist.c \
          src/carray/carray.c \
          src/cstring/cstring.c

.PHONY: build

build: compile
	$(info [+] Building $(notdir $(TARGET)))
	$(AR) cr $(TARGET) $(BUILD)/obj/*.o

compile: install-headers
	$(info [+] Compiling sources)
	for file in $(SRC); do \
		$(CC) -c $(CFLAGS) $$file -o "$(BUILD)/obj/$$(basename $${file%.*}).o"; \
	done

install-headers: prepare
	$(info [+] Installing headers)
	cp src/memory.h $(PREFIX)/include/cds
	cp src/clist/clist.h $(PREFIX)/include/cds
	cp src/carray/carray.h $(PREFIX)/include/cds
	cp src/cstring/cstring.h $(PREFIX)/include/cds

prepare:
	$(info [+] Creating directories)
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/obj
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/include/cds

clean:
	$(info [+] Cleaning up)
	rm -rf $(BUILD)/obj

test: build
	$(info [+] Running tests)
	for file in test/*.c; do \
		$(CC) $(CFLAGS) -L$(PREFIX)/lib $$file -lcds -o "$(BUILD)/bin/$$(basename $${file%.*})" 2>/dev/null; \
	done
	./test/run $(BUILD)/bin

$(V).SILENT:
