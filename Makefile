CC = gcc
SRCS_C = src/win.c src/context.c src/list.c src/interactive.c src/event.c
OBJS = $(SRCS_C:.c=.o)
LIBOUT = lib/libpyramid.so
LIBS = -lcairo -lglfw -lGL -lGLEW -lm
INCLUDE_DIR = src/include
CFLAGS = -fPIC -I$(INCLUDE_DIR)

all: build testbed run

build: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $(LIBOUT) $(OBJS) $(LIBS)

install:
	install $(LIBOUT) /usr/lib
	install $(INCLUDE_DIR)/* -t /usr/include/pyramid

.PHONY: testbed
testbed:
	make -C testbed

.PHONY: run
run:
	./bin/testbed

.PHONY: clean
clean:
	find . -name "*.o" -exec rm -f {} \;
	make clean -C testbed
