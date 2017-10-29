# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm -lpng

SRCDIR := src
OBJDIR := obj

# add source files here
SRCS := $(wildcard $(SRCDIR)/*.c)
HDRS := $(wildcard $(SRCDIR)/*.h)

# generate names of object files
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# name of executable
EXEC := game

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(SRCS) $(HDRS) Makefile
	$(CC) -o $@ $(@:$(OBJDIR)/%.o=$(SRCDIR)/%.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
