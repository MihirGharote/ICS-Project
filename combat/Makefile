CC = gcc
CFLAGS = -pedantic -Wall -Wextra -Wconversion -Wsign-conversion -DRUNCOMBAT=1

TARGET = combat_main

# INFO: To add new compile folders, add them below, separated by spaces
SRCDIRS = .
# INFO: Add additional libraries below, like -lm
LIBS = -lncurses -lm

SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))

.PHONY: clean run

$(TARGET): $(SRCS) ../globals.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm $(TARGET)

run: $(TARGET)
	@./$(TARGET)
