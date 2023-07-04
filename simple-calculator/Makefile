##
# General purpose makefile for this folder
#
# @file
# @version 0.1
#
CC = gcc
CFLAGS = -Wall -g -std=c11
SRCS = calculator.c
OBJDIR = build
OBJS = $(OBJDIR)/$(notdir $(SRCS:.c=.o))


.PHONY: all clean

all: $(OBJDIR) $(basename $(SRCS))


$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(basename $(SRCS)): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJDIR) $(basename $(SRCS))

run: $(basename $(SRCS))
	./$(basename $(SRCS))


# end
