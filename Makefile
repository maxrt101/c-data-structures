# c-data-structures

export CC     := gcc
export AR     := ar
export CFLAGS := -c -Isrc/

NAME          := cds
LIBNAME       := lib$(NAME).a
OBJS          := $(addsuffix .o, $(basename $(wildcard src/*.c src/*/*.c)))

.PHONY: all

all: prepare compile clean

compile: $(OBJS)
	rm -f bin/$(LIBNAME)
	$(AR) cr bin/$(LIBNAME) $(OBJS)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) $< -o $@

prepare:
	mkdir -p bin

clean:
	rm $(OBJS)

