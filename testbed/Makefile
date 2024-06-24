CC = gcc
SRCS_C = src/main.c src/scene.c
OBJS = $(SRCS_C:.c=.o)
EXE = ../bin/testbed
LIBS = -L../ -l:lib/pyramid.so -lglfw -lGL -lcairo -lm
INCLUDE_DIR = ../src/include
CFLAGS = -I$(INCLUDE_DIR)

build: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

.PHONY: clean
clean:
	find . -name "*.o" -exec rm -f {} \;
