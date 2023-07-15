# specify your source files here
SRCS = $(wildcard *.c)

# specify your object files here
OBJS = $(addprefix build/,$(notdir $(SRCS:.c=.o)))

# specify your compiler flags here
CFLAGS = -Wall -ggdb -std=c11 

# specify your compiler
CC = gcc

# default command to compile your program
all: build/my_program

build/my_program: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# a command to clean up your build directory
clean:
	rm -f build/*

# a command to run your program
run: build/my_program
	./build/my_program
